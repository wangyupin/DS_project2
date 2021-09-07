#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

class Node{
    public:
        int row,col,dist;
        Node* left;
        Node* right;
        Node* up;
        Node* down;
        Node* parent;
    Node(int row=0,int col=0,int dist=0,Node* parent=NULL):
        row(row),col(col),dist(dist),parent(parent){
            left=NULL;
            right=NULL;
            up=NULL;
            down=NULL;
        }
};

void run(Node* cur_Node);

struct info{
    char floor;
    int visit;
    int dist;
};

queue <Node*> path;
int cnt=0;
int life;
Node* root;
int main(int argc,char *argv[]){
    ifstream fin(argv[1]);
    if(!fin)
        cout<<"Error in reading files"<<endl;
    ofstream fout("final.path");
    if(!fout)
        cout<<"Error in output results"<<endl;
    int row,col;

    fin>>row>>col>>life;
    info map[row+1][col+1];
    fin.get();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fin>>map[i][j].floor;
            map[i][j].visit=0;
            map[i][j].dist=-1;
            if(map[i][j].floor=='R'){
                root=new Node(i,j,0,NULL);
                map[i][j].dist=0;
            }
        }
        fin.get();
    }

    //°µbfs,«Øtree
    queue<Node*> q1;
    q1.push(root);
    while(!q1.empty()){
        int r,l,d;
        Node* cur_Node=q1.front();
        r=cur_Node->row;
        l=cur_Node->col;
        d=cur_Node->dist;
        if(map[r][l-1].floor=='0'&&map[r][l-1].visit==0&&l-1>=0){
            map[r][l-1].visit=1;
            map[r][l-1].dist=d+1;
            Node* new_node=new Node(r,l-1,d+1,cur_Node);
            cur_Node->left=new_node;
            q1.push(new_node);
        }
        if(map[r-1][l].floor=='0'&&map[r-1][l].visit==0&&r-1>=0){
            map[r-1][l].visit=1;
            map[r-1][l].dist=d+1;
            Node* new_node=new Node(r-1,l,d+1,cur_Node);
            cur_Node->up=new_node;
            q1.push(new_node);
        }
        if(map[r][l+1].floor=='0'&&map[r][l+1].visit==0&&l+1<col){
            map[r][l+1].visit=1;
            map[r][l+1].dist=d+1;
            Node* new_node=new Node(r,l+1,d+1,cur_Node);
            cur_Node->right=new_node;
            q1.push(new_node);
        }
        if(map[r+1][l].floor=='0'&&map[r+1][l].visit==0&&r+1<row){
            map[r+1][l].visit=1;
            map[r+1][l].dist=d+1;
            Node* new_node=new Node(r+1,l,d+1,cur_Node);
            cur_Node->down=new_node;
            q1.push(new_node);
        }
        q1.pop();
    }
    Node* cur_Node=root;
    run(root);
    fout<<path.size()-1<<endl;
    int num=0;
    while(!path.empty()){
        //map[path.front()->row][path.front()->col].visit=2;
        fout<<path.front()->row<<" "<<path.front()->col<<endl;
        path.pop();
        num++;
    }

}

void run(Node* cur_Node){
    if(cur_Node!=NULL){
        path.push(cur_Node);
        //cout<<"row= "<<cur_Node->row<<" col= "<<cur_Node->col;
        //cout<<" cur_Node->dist= "<<cur_Node->dist<<" cnt= "<<cnt<<" total= "<<cur_Node->dist+cnt<<endl;
        if(cur_Node->dist+cnt>=life-1){
            //cout<<cur_Node->row<<" "<<cur_Node->col<<endl;
            Node* temp=cur_Node->parent;
            stack<Node*> temp_stack;
            while(temp!=root){
                //cout<<"row= "<<temp->row<<" col= "<<temp->col<<endl;
                path.push(temp);
                temp_stack.push(temp);
                temp=temp->parent;
            }
            path.push(temp);
            while(!temp_stack.empty()){
                path.push(temp_stack.top());
                temp_stack.pop();
            }
            path.push(cur_Node);
            cnt=cur_Node->dist;
        }
        if(cur_Node->up!=NULL){
            cnt++;
            run(cur_Node->up);
            path.push(cur_Node);
            cnt++;
        }
        if(cur_Node->left!=NULL){
            cnt++;
            run(cur_Node->left);
            path.push(cur_Node);
            cnt++;
        }
        if(cur_Node->right!=NULL){
            cnt++;
            run(cur_Node->right);
            path.push(cur_Node);
            cnt++;
        }
        if(cur_Node->down!=NULL){
            cnt++;
            run(cur_Node->down);
            path.push(cur_Node);
            cnt++;
        }
    }
}
