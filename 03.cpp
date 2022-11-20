#include<iostream>
#include<cmath>
#include<string.h>                         //store->retail | wholesale -> customer
using namespace std;
class Store{
    protected:
    int *stockqty;
    int *soldqty;
    string *itemname;
    int titem;
    
    public:
         void getdata(){
            cout<<"Enter item to register:"<<endl;
            cin>>titem;
            itemname=new string [titem];
            stockqty=new int [titem];
         for(int i=0;i<titem;i++){
            cout<<"Enter Item Name :";
            cin>>itemname[i];
            cout<<"Enter Qty :";
            cin>>stockqty[i];
            }   
        }
        
};
class Retail: virtual protected Store{
    protected:
    int *rprice;
    public:
        
        void getdata(){
            cout<<"\n******** updating GRN-Retail  ********\n";
            rprice= new int [titem];
            
            cout<<"\n***** Set Sell Price for RETAIL ***********\n";
            for(int i=0;i<titem;i++){
                cout<<"Enter Sell Price for "<<itemname[i]<<":"<<endl;
                cin>>rprice[i];
            }
            cout<<"\n******** GRN-Retail settled Successfully ********\n";
            cout<<"******** "<<titem<< " qty updated ********\n";
        }
        void displayallitem(){
            for(int i=0;i<titem;i++){
            cout<<"Item Name: "<<itemname[i]<<endl;
            cout<<"Retail Price :Rs. "<<rprice[i]<<endl;
            cout<<"Total Qty in Stock : "<<stockqty[i]<<"pc"<<endl;
            }
            // cout<<"Total Qty sold:"<<stockqty-soldqty<<endl;
        }
};
class Wholesale: virtual protected Store{
    protected:
    int *wprice;
    int *minqty;
    public:
        
        void getdata(){
            cout<<"\n******** updating GRN-Wholesale  ********\n";
            wprice= new int [titem];
            minqty=new int [titem];
            
            cout<<"\n***** Set Sell Price for Wholesale ***********\n";
            for(int i=0;i<titem;i++){
                cout<<"Enter Sell Price for "<<itemname[i]<<":"<<endl;
                cin>>wprice[i];
                cout<<"Enter Min Qty to be sell :"<<endl;
                cin>>minqty[i];
            }
            cout<<"\n******** GRN-Wholesale settled Successfully ********\n";
            cout<<"******** "<<titem<< " qty updated ********\n";
        }
        void displayallitem(){
            for(int i=0;i<titem;i++){
            cout<<"Item Name: "<<itemname[i]<<endl;
            cout<<"Wholesale Price :Rs. "<<wprice[i]<<endl;
            cout<<"Total Min Qty in Stock : "<<minqty[i]<<"pc"<<endl;
            cout<<"Total Qty in Stock for wholesale : "<<floor(stockqty[i]/minqty[i])<<"pc"<<endl;  //Total Set in Stocks
            
            }
            // cout<<"Total Qty sold:"<<stockqty-soldqty<<endl;
        }
};
class Admin:virtual public Store,virtual public Retail,virtual public Wholesale{
    int option;
    string pwd="1234";
    string enteredpwd;
    public:
        
        Admin(){
            
            
            

            try {
                cout << "Enter pwd to access as Admin: ";
                cin>>enteredpwd;
                if (pwd != enteredpwd)
                {
                    throw pwd;
                }
                else{
                    cout<<"\n Access Granted !\n";
                        
                        Store::getdata();
                        char opt='Y';
                        while(opt!='N'){
                            cout<<"Enter Option to modify \t 1.Retail \2.Wholesale :";
                            cin>>option;
                            if(option==1)
                                Retail::getdata();
                            else{
                                Wholesale::getdata();

                            }
                            cout<<"Entered choice again :";
                            cin>>opt;
                        }
                        

                }
            }

            catch (string pwd) {
                cout << "Incorrect Pwd retry! \n";
            }
            
        }

            
        
        void displayallitem(){
            for(int i=0;i<titem;i++){
            cout<<"Item Name: "<<itemname[i]<<endl;
            cout<<"Retail Price :Rs."<<rprice[i]<<endl;
            cout<<"Wholesale Price :Rs."<<wprice[i]<<endl;
            cout<<"Total Min Qty in Stock-Wholesale : "<<minqty[i]<<"pc"<<endl;
            cout<<"Total Qty in Stock for wholesale : "<<floor(stockqty[i]/minqty[i])<<"pc"<<endl;  //Total Set in Stocks
            cout<<"Total Qty in Retail :"<<stockqty[i]<<"pc"<<endl;
            
            }
        }
};
class Customer: virtual public Store,virtual public Retail,virtual public Wholesale{
    protected:
    string custname;
    string add;
    
    int torder=0;
    private:
    int phoneno;
    public:
    string itemorder[10]={"null"};
    int qtyorder[10]={0};
    int itemno;
        Customer(){
            cout<<"Enter Customer name :";
            getline(cin, custname);
            cin.ignore();
            cout<<"Enter address :";
            getline(cin, add);
            cin.ignore();
            cout<<"Enter phone number :";
            
            cin>>phoneno;
            

        }
        void order(){
            for(int i=0;i<titem;i++){
                cout<<i<<".\t"<<itemname[i]<<"\t ";
                if(stockqty[i]!=0){
                    cout<<"In stock"<<endl;
                }
                else{
                    cout<<"out of stock"<<endl;
                }
            }
            cout<<"Create your list !\n";
            int opt=1;
            while(opt!=0){
                cout<<"Enter item no:";
                cin>>itemno;
                cout<<"Enter qty to order :";
                cin>>qtyorder[itemno];
                if(itemno<titem && itemno>=1){
                    cout<<itemname[itemno]<<"Added into cart "<<endl;
                    itemname[itemno]=itemorder[itemno];
                    torder++;
                }
                cout<<"Enter more item 1 for more 0 for not :";
                cin>>opt;
            }

        }
        void displaycart(){
            for(int i=0;i<10;i++){
                
                if(qtyorder[i]!=0 || itemorder[i]!="null"){
                    cout<<"Item Name :"<<itemorder[i]<<endl;
                    cout<<"Qty :"<<qtyorder[i]<<endl;
                }
            }
        }



};
int main(){
    Admin A;
    A.displayallitem();
    Customer B;
    B.order();
    B.displaycart();
    return 0;
}