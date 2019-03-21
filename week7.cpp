#include <iostream>
using namespace std;

class Node 
{
	public:
	int data;
	Node *parent, *left, *right;
	Node(int val)
	{parent=NULL;left=NULL;right=NULL;data=val;}
};

class Btree
{
	
	public:
	Node *root;
	Btree()
	{root = NULL;}	
	void insert(int value);
	void inserthelp(Node *curr, int value);
	void display();void displayhelp(Node *curr,int space);
	Node *search(int val);
	Node *find_min(Node *curr);
	void replace(Node *curr, Node *rep);
	void del(int data);
};

void Btree::insert(int value)
{
	inserthelp(root,value);
}

void Btree::inserthelp(Node *curr,int value)
{
	if(root==NULL)
	{root= new Node(value);}
	
	else if(value<curr->data)
	{
		if(curr->left==NULL)
		{curr->left=new Node(value);curr->left->parent=curr;}
		
		else	
		inserthelp(curr->left,value);
	}
	
	else if(value>curr->data)
	{
		if(curr->right==NULL)
		{curr->right=new Node(value);curr->right->parent=curr;}
		
		else	
		inserthelp(curr->right,value);
	}

	else
	return;
}

void Btree::display()
{
	displayhelp(root,0);
}

void Btree::displayhelp(Node *curr , int space)
{
	if(curr->right!=NULL)
	{displayhelp(curr->right,space+1);}

	for(int i=space; i>0;i--)
	cout<<"   ";
	
	cout<<curr->data<<"\n";	
	
	if(curr->left!=NULL)
	{displayhelp(curr->left,space+1);}
}	

Node *Btree::search(int val)
{
	Node *ptr=root;	
	while(ptr!=NULL)
	{
		if(ptr->data==val)
		return ptr;
		
		else if(ptr->data > val)
		ptr=ptr->left;
		
		else
		ptr=ptr->right;
	 }
	return ptr;
}

Node *Btree::find_min(Node *curr)
{
	while(curr->left!=NULL)
	curr=curr->left;
	
	return curr;
}

void Btree::replace(Node *curr, Node *rep)
{
	Node *par=curr->parent;
	if(curr!=root)
	{
		if(curr==par->left)
		{par->left=rep;}
		else if(curr==par->right)
		{par->right=rep;}
		rep->parent=curr->parent;
	}
	else if(curr==root)
	{
		root=rep;
		rep->left=curr->left;
		rep->left->parent=rep;
		
		if(rep->parent!=curr)		
		{
			if(rep->right)
			replace(rep,rep->right);
		
			else
			{rep->parent->left=NULL;}
		 		
			rep->right=curr->right;
			rep->right->parent=rep;
		}
		rep->parent=NULL;
		
	}
}

void Btree::del(int val)
{
	Node *curr=search(val);
	Node *ptr=find_min(curr->right);
	replace(curr,ptr);
	delete curr;
}

int main()
{
	Btree b;
	b.insert(4);b.insert(3);b.insert(2);b.insert(1);b.insert(6);b.insert(7);b.insert(5);b.insert(9);
	b.display();
	
	cout<<"-------------------------------------------------------------"<<endl;
	cout<<"Minimum value = "<<b.find_min(b.root)->data<<endl;
	b.del(4);
	b.display();
	cout<<"-------------------------------------------------------------"<<endl;
	b.del(5);
	b.display();
	cout<<"-------------------------------------------------------------"<<endl;
	return 0;
}
