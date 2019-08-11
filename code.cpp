#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
class node
{

    public:
        string value;
        int visited;
        int weight;
        node *next[5]={NULL};
};
int n;
int max1;
int max2;
int max_index;

node* create_node(string a)
{
    node *temp=new node;
    temp->value=a;
    temp->visited=0;
    temp->weight=INT_MAX;
    return temp;
}

int find_index(int index)
{
    if(index==0)
    {
        index=0;
    }
    else if(index==2)
    {
        index=1;
    }
    else if(index==6)
    {
        index=2;
    }
    else if(index==19)
    {
        index=3;
    }
    else
        index=4;

        return index;
}
void diversion(string sub,int count,string existing_string,node *temp,int index,int end)
{
    string left=sub.substr(count,sub.length()-count+1);
    string right=existing_string.substr(count,existing_string.length()-count+1);
    int left_index=find_index(left[0]-97);
    int right_index=find_index(right[0]-97);
    temp->value=existing_string.substr(0,count);
    int a,b;
    a=end-left.length();
    b=end-count;

    if(right.length())
    {
        node *aux[5]={NULL};
        for(int ab=0;ab<5;ab++)
        {
            if(temp->next[ab])
                aux[ab]=temp->next[ab];
        }
        temp->next[right_index]=create_node(right);

        for(int i=0;i<5;i++)
        {


            temp->next[right_index]->next[i]=aux[i];
            if(i!=right_index)
            {
                temp->next[i]=NULL;
            }
        }
    }
    if(left.length())
    {
        temp->next[left_index]=create_node(left);
    }
}

int flag=0;
void check(node *temp,string sub,int index,int end)
{
    int count=0;
    string existing_string=temp->next[index]->value;
    while(1)
    {   if(flag==1)
        return ;
        if(count==sub.length())
        {
            break;
        }
        else if(sub[count]==existing_string[count])
        {
            count++;
        }
        else if(sub[count]!=existing_string[count] && existing_string[count]!=NULL)
        {
            diversion(sub,count,existing_string,temp->next[index],index,end);
            flag=1;
        }
        else if(existing_string[count]==NULL)
        {
            int index_sub=find_index(sub[count]-97);
            if(temp->next[index]->next[index_sub])
            {
                sub=sub.substr(1,sub.length()-1);
                check(temp->next[index],sub,index_sub,end);
            }
            else
            {
                 diversion(sub,count,existing_string,temp->next[index],index,end);
                 flag=1;
            }
        }
    }
}

void build_tree(string seq, node* root)
{
    seq=seq+"{";
    node *temp=root;
    int end=seq.length()-1;
    for(int i=end;i>=0;i--)
    {
        int index=find_index(seq[i]-97);
        string sub=seq.substr(i,end-i+1);
        if(temp->next[index])
            {
                flag=0;
                check(temp,sub,index,end);
            }
        else
            {
                temp->next[index]=create_node(sub);
            }
    }
}

int check_motif_length(string may_be_motif ,node* temp,int index)
{
    int c=0;
    int ce=1;
    int index_char=find_index(may_be_motif[c]-97);
    while(1)
    {
        if(temp->next[index_char] && temp->next[index_char]->visited==index-1 && may_be_motif.length()>1)
        {
            string existing_string=temp->next[index_char]->value;
            may_be_motif=may_be_motif.substr(1,may_be_motif.length()-1);
            if(may_be_motif[c]==existing_string[ce])
            {
                ce++;
            }
            else if(may_be_motif[c]!=existing_string[ce] && existing_string[ce]!=NULL)
            {
                return 0;
            }
            else if(may_be_motif[c]!=existing_string[ce] && existing_string[ce]==NULL)
            {
                if(check_motif_length(may_be_motif,temp->next[index_char],index))
                {
                    temp->next[index_char]->visited=index;
                    return 1;
                }
            else return 0;
            }
        }
        else if(temp->next[index_char] && temp->next[index_char]->visited==index-1 && may_be_motif.length()==1)
        {
            temp->next[index_char]->visited=index;
            return 1;
        }
        else return 0;
    }
}

void find_motif_klength(string seq,node* temp,int index,int length)
{
    int n=seq.length()-1;
    for(int i=0;i<=n-length+1;i++)
    {
            string may_be_motif=seq.substr(i,length);
            check_motif_length(may_be_motif,temp,index);
    }

}


int weight_yes=0;
int max_length=0;
string temp="";
string max_length_motif="";

void print_unknown_length(node* pr )
{
    if(pr->visited==n-1)
    {
            weight_yes=weight_yes+pr->weight;


            temp=temp+pr->value;

    }
    if (pr->next[0] == NULL && pr->next[1] == NULL && pr->next[2] == NULL && pr->next[3] == NULL && pr->next[4] == NULL)
    {
        if(max_length<weight_yes)
        {
            max_length=weight_yes;
            max_length_motif=temp;

        }
    weight_yes=0;
    temp="";
    return;
    }

    if(pr->next[0] && pr->next[0]->visited==n-1)
    print_unknown_length(pr->next[0]);
    if(pr->next[1] && pr->next[1]->visited==n-1)
    print_unknown_length(pr->next[1]);
    if(pr->next[2] && pr->next[2]->visited==n-1)
    print_unknown_length(pr->next[2]);
    if(pr->next[3] && pr->next[3]->visited==n-1)
    print_unknown_length(pr->next[3]);
    if(pr->next[4] && pr->next[4]->visited==n-1)
    print_unknown_length(pr->next[4]);
}

int ce=1;
int check_motif_unknown_length(string may_be_motif ,node* temp,int index,int len)
{
    int c=0;
    ce=1;

    int index_char=find_index(may_be_motif[c]-97);

    while(1)
    {
        if(temp->next[index_char] && temp->next[index_char]->visited==index-1 && may_be_motif.length()>1)
        {
            string existing_string=temp->next[index_char]->value;
            may_be_motif=may_be_motif.substr(1,may_be_motif.length()-1);
            if(may_be_motif[c]==existing_string[ce])
            {
                ce++;
            }
            else if(may_be_motif[c]!=existing_string[ce] && existing_string[ce]!=NULL)
            {
                if(temp->next[index_char]->weight>ce &&temp->next[index_char]->visited==(index-1))///******
                {
                   ce=1;
                }
                return 0;
            }
            else if(may_be_motif[c]!=existing_string[ce] && existing_string[ce]==NULL)
            {
                if(temp->next[index_char]->weight>ce &&temp->next[index_char]->visited==(index-1))////****
                {
                    temp->next[index_char]->weight=ce;
                    ce=1;
                }
                if(check_motif_unknown_length(may_be_motif,temp->next[index_char],index,len))
                {
                    temp->next[index_char]->visited=index;
                    return 1;
                }

                else
                    return 0;
            }
        }
        else if(temp->next[index_char] && temp->next[index_char]->visited==index-1 && may_be_motif.length()==1)
        {
            if(temp->next[index_char]->weight>ce &&temp->next[index_char]->visited==(index-1))///****
            {
                temp->next[index_char]->weight=ce;
            }
            temp->next[index_char]->visited=index;
            if(len>max2)
                max2=len;
            return 1;
        }

        else {
                return 0;
            }
}
}

void find_motif_unknown_length(string seq,node* temp,int index)
{   seq=seq+"{";
    int n=seq.length()-1;
    for(int i=0;i<n-1;i++)
    {   for(int j=0;j<=i+1;j++)
        {
            string may_be_motif=seq.substr(j,n-i);
            if(may_be_motif.length()<=max1 && may_be_motif.length()>1)
            {
                int length=may_be_motif.length();
                check_motif_unknown_length(may_be_motif,temp,index,length);
            }

        }
        if(max1>max2 && max2!=0)
            {
                max1=max2;
            }
    }
}

string motif_k_length="";
void print_klength(node* pr )
{
    if (pr== NULL )
    {
        return;
    }
    if(pr->visited==n-1)
    {
       motif_k_length=motif_k_length+pr->value;
    }

    print_klength(pr->next[0]);
    print_klength(pr->next[1]);
    print_klength(pr->next[2]);
    print_klength(pr->next[3]);
    print_klength(pr->next[4]);
}

int main()
{
    cin.clear();
    fflush(stdin);
    cout<<"enter number of DNA sequences"<<endl;
    cin>>n;

    cout<<"enter your DNA sequence:"<<endl;
    string sequences[n];
    node *root;
    root=create_node("root");
    for(int i=0;i<n;i++)
    {
        cout<<"sequence number   "<<i+1<<endl;
        cin>>sequences[i];
        cout<<endl;
    }
    auto start = high_resolution_clock::now();
    build_tree(sequences[0],root);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<< "Time taken by build function: "<< duration.count() << " microseconds" << endl;
    cout<<"enter 1 for length and 2 for unknown length"<<endl;
    int choose=0;
    cin>>choose;


    if(choose==1)
    {
        int length;
        cout<<"enter length"<<endl;
        cin>>length;
        auto start1 = high_resolution_clock::now();

        for(int i=1;i<n;i++)
        {
            find_motif_klength(sequences[i],root,i,length);
        }
        auto stop1 = high_resolution_clock::now();
        print_klength(root);
        cout<<"your motif is:   ";
        cout<<motif_k_length.substr(0,length)<<endl;
        cout<<endl;

        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        cout << "Time taken by check function: "<< duration1.count() << " microseconds" << endl;
    }
    else if(choose==2)
    {
        auto start2 = high_resolution_clock::now();
        max1=sequences[1].length();
        max2=0;
        for(int i=1;i<n;i++)
        {
            find_motif_unknown_length(sequences[i],root,i);
        }
        print_unknown_length(root);
        cout<<"your motif is:   ";

        cout<<max_length_motif.substr(0,max_length)<<endl;
        cout<<endl;
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        cout << "Time taken by check function: "<< duration2.count() << " microseconds" << endl;
    }
return 0;
}
