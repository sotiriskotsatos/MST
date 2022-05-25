#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <math.h>
using namespace std;

struct lineContent
{
    int town1;
    int town2;
    int gas;
};

struct node
{
    lineContent data;
    struct node* next;
};

void getNodes_Edges(ifstream& inF, int& nds, int& eds)
{
    string s;
    getline(inF, s);
    stringstream str_toInt(s);
    str_toInt >> nds;
    str_toInt >> eds;
}


void getTowns_Gas(string line, int& town_1, int& town_2, int& gasL)
{
    stringstream str_toInt(line);
    str_toInt >> town_1;
    str_toInt >> town_2;
    str_toInt >> gasL;
}

bool existInArray(int* arr, int t1, int t2, int arraySize, bool& b1, bool& b2)
{
    b1 = b2 = false;
    for (int i = 0; i < arraySize; i++)
    {
        if (arr[i] == t1) {
            b1 = true;
            if (b2) {
                return true;
            }
            else {
                continue;
            }
        }
        else if (arr[i] == t2) {
            b2 = true;
            if (b1) {
                return true;
            }
            else {
                continue;
            }
        }
    }
    return false;
}

class linked_list //https://www.geeksforgeeks.org/cpp-program-for-sorting-linked-list-which-is-already-sorted-on-absolute-values/
{
private:
    node* head;
public:
    linked_list()
    {
        head = NULL;
    }
    void add_node(lineContent n)
    {
        node* tmp = new node;
        tmp->next = head;
        tmp->data = n;
        head = tmp;
    }
    void sortList(int length)
    {
        for (int i = 0; i < length; i++) {
            node* prev = head;
            node* curr = head->next;

            while (curr != NULL)
            {
                if (curr->data.gas < prev->data.gas)
                {
                    prev->next = curr->next;
                    curr->next = head;
                    head = curr;
                    curr = prev;
                }
                else {
                    prev = curr;
                }
                curr = curr->next;
            }
        }
    }
    int getMax(int arraySize)
    {
        node* tmp;
        tmp = head;
        int counter = 0;
        int max = 0;
        bool b1, b2;
        int* nodesUsed = new int[arraySize];
        for (int i = 0; i < arraySize; i++) {
            nodesUsed[i] = -1;
        }
        while (tmp != NULL)
        {
            if (!existInArray(nodesUsed, tmp->data.town1, tmp->data.town2, arraySize, b1, b2))
            {
                if (!b1) {
                    nodesUsed[counter] = tmp->data.town1;
                    counter++;
                    max = tmp->data.gas;
                }
                if (!b2) {
                    nodesUsed[counter] = tmp->data.town2;
                    counter++;
                    max = tmp->data.gas;
                }
            }
            tmp = tmp->next;
        }
        return max;
    }
};

int calcResult(ifstream& inF, int nodesCnt,int edgesCnt)
{
    string s;
    linked_list lst;
    while (getline(inF, s))
    {
        int tn1, tn2, gs;
        getTowns_Gas(s, tn1, tn2, gs);
        s.clear();
        lineContent lC;
        lC.town1 = tn1;
        lC.town2 = tn2;
        lC.gas = gs;
        lst.add_node(lC);
    }
    lst.sortList(edgesCnt);
    return lst.getMax(nodesCnt);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "Please enter a txt file" << endl;
        return -1;
    }
    ifstream inFile(argv[1]);
    if (inFile.is_open())
    {
        int nodes, edges;
        getNodes_Edges(inFile, nodes, edges);
        cout << calcResult(inFile, nodes,edges);
        inFile.close();
    }
    else cout << "Unable to open file " << argv[1];
    return 0;
}
