#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "string"
#include "fstream"
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"


using namespace std;

struct student
{
    string name;
    int randomnumber;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & name;
		ar & randomnumber;
	}
};


int main()
{
    setlocale(LC_ALL, "Russian");


    cout << "Erofeev queue generator" << endl;
    cout << "� ������� �� �������� ���� ������:" << endl;

    //������ ��� ���������
    string names[19]={
    "���� ��������",
    "������� �������",
    "���� ������",
    "��������� �����",
    "������ �������",
    "������ �����������",
    "������ ������",
    "���� ��������",
    "����� �������",
    "����� ���������",
    "������ ���������",
    "������ ��������",
    "��������� �������",
    "��������� �������",
    "Ը��� �����",
    "�������� �������",
    "����� �����������",
    "���������� ��������",
    "������ �������"};

    srand(time(0));

    student students[19];

    for(int i=0; i<19;i++)
    {
        students[i].name = names[i];
        students[i].randomnumber = rand() % 10000;
    }

    //���������� �� ����������� randomnumber
    for(int i=0;i<19;i++)
    {
        for(int j=i; j<19;j++)
        {
            if (students[j].randomnumber < students[i].randomnumber)
            {
                //�������� ���������
                student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    

	//������ � ����
	ofstream file("output.txt", ios_base::out);
	boost::archive::text_oarchive oa(file);
	for (int i = 0; i < 19; i++)
		oa << students[i];
	file.close();

	//�������� ������� ������� ���������
	student students2[19];

	//������ �� �����
	ifstream file2("output.txt");
	boost::archive::text_iarchive ia(file2);
	for (int i = 0; i < 19; i++)
		ia >> students2[i];

	for(int i=1; i<20; i++)
	cout << i << ") " << students2[i-1].name <<", ���������� ����� - "<< students2[i-1].randomnumber << endl;

    cin.get();
    return 0;
}
