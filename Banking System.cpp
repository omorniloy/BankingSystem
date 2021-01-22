// header files
#define BRANCH 2
#define HOLDER 2
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

//classes
class accountHolder
{
private:
    int acNumber;
    float balance;
    string name;
    static int branch, holder;
public:
    accountHolder() : balance(0){                   //no argument constructor
    }
    accountHolder(float bal) : balance(bal){        //constructor
    }
    ~accountHolder(){                               //destructor
    }
    void setacNumber()
    {
        acNumber=11*10000+((branch+1)*100)+(holder+1);
        ++holder;
        if (holder==HOLDER)
        {
            ++branch;
            holder=0;
        }
    }
    void setbalance(float bal)
    {
        balance=bal;
    }
    void setname(string nm)
    {
        name=nm;
    }

    int getacNumber()const
    {
        return acNumber;
    }
    float getbalance()const
    {
        return balance;
    }
    string getname()const
    {
        return name;
    }

    void showacNumber()const
    {
        cout<<"\t\tAccount Number: "<<acNumber<<endl;
    }
    void showbalance()const
    {
        cout<<"\t\tBalance: "<<balance<<endl;
    }
    void showname()const
    {
        cout<<"\t\tName: "<<name<<endl;
    }

    void inputacNumber()
    {
        cout<<"\t\tAccount number: "<<acNumber<<endl;

    }
    void inputbalance()
    {
        cout<<"\t\tEnter balance: ";
        cin>>balance;
    }
    void inputname()
    {
        cout<<"\t\tEnter name: ";
        fflush(stdin);
        getline(cin,name);
    }

    void withdraw()
    {
        int with;
        cout<<"\t\tHow much you want to withdraw: ";
        while(cin>>with)
        {
            if (balance>with)
                balance=balance-with;
            else
            {
                cout<<"\t\tYou don't have enough money"<<endl;
                cout<<"\t\tHow much money you want to withdraw: "<<endl;
                continue;
            }
            break;
        }
    }
    void deposit()
    {
        int depo;
        cout<<"\t\tHow much you want to deposit: ";
        cin>>depo;
        balance=balance+depo;
    }
    void interest()
    {
        balance=balance+(0.02*balance);
    }

    friend ostream &operator <<(ostream &output, const accountHolder &b)    //overload insertion operator
    {
         output <<"\t\tBalance: "<<b.balance<<endl;
         return output;
    }
};

class Loan
{
protected:
    float loan;
public:
    Loan(): loan(){
    }
    ~Loan(){
    }
    void setloan(float l)
    {
        loan=l;
    }
    float getloan()
    {
        return loan;
    }
    void showloan()
    {
        cout<<"\t\tAmount of loan with interest: "<<loan<<endl;
    }
    void inputloan()
    {
        cout<<"\t\tEnter loan:";
        cin>>loan;
    }
};

class loanAccountHolder : public accountHolder, public Loan     //multiple inheritance
{
public:
    void withdrawLone()
    {
        float amount;
        cout<<"\t\tHow much you want to withdraw loan: ";
        cin>>amount;
        loan=amount+ (amount*0.15);
    }
};

class branch
{
private:
    float total;
public:
    branch (): total(0){
    }
    branch (float ttl): total(ttl){
    }
    ~branch() {
    }
    void settotal(int t)
    {
        total=t;
    }
    float gettotal()const
    {
        return total;
    }
    void showtotal()const
    {
        cout<<"\t\tEnd of the day total balance :"<<total<<endl;
    }
    void inputtotal()
    {
        cout<<"\t\tEnter total : "<<endl;
        cin>>total;
    }
    void calculateTotal(float b)
    {
        total+=b;
    }

};

class employee                                  // abstract base class
{
protected:
    string name;
    int id;
public:
    employee () : name(), id() {
    }
    employee (string nam, int nmbr) : name(nam), id(nmbr){
    }
    ~employee(){
    }
};

class bonusEmployee : public employee           //derived class ,multi-level inheritance
{
protected:
    float bonus;
public:
    bonusEmployee(): bonus () {
    }
    bonusEmployee (float bon) : bonus(bon) {
    }
    ~bonusEmployee() {
    }
    void setbonus(int b)
    {
        bonus=b;
    }
    float getbonus()const
    {
        return bonus;
    }
    void showbonus()const
    {
        cout<<" bonus: "<<bonus<<endl;
    }
    void inputbonus()
    {
        cout<<"\t\tEnter accountant bonus: "<<endl;
        cin>>bonus;
    }

    void calculateBonus(int startAcHolder, int endAcHolder, accountHolder a[][HOLDER],int branchNmbr, float percentage)
    {
        for(int j= startAcHolder; j<endAcHolder; j++)
            bonus += a[branchNmbr][j].getbalance()*percentage;
    }
};

class accountant : public bonusEmployee             // derived class, multi-level inheritance
{
public:
    accountant () : bonusEmployee(){
    }
    ~accountant (){
    }
};

class manager : public bonusEmployee                // derived class, multi-level inheritance
{
public:
    manager () : bonusEmployee(){
    }
    ~manager(){
    }
};

class owner : public bonusEmployee                  // derived class, multi-level inheritance
{
private:
    accountant actnt[BRANCH][2];                    // aggregation
    manager m[BRANCH];
public:
    void calculateBonus(int startAcHolder, int endAcHolder, accountHolder a[][HOLDER],int branchNmbr, float percentage) //overriding
    {
        for(int j= startAcHolder; j<endAcHolder; j++)
            bonus += a[branchNmbr][j].getbalance()*percentage;

        for(int j=0; j<BRANCH; j++)
            for(int k=0; k<2; k++)
                bonus += actnt[BRANCH][k].getbonus() + m[BRANCH].getbonus();
    }
};

//assing value in static variable
int accountHolder::branch=0;
int accountHolder::holder=0;

// main function
int main()
{
    int i,j,k,a,choise;
    accountHolder account[BRANCH][HOLDER];
    branch bra[BRANCH];
    accountant actnt[BRANCH][2];
    manager m[BRANCH];
    owner own;
    loanAccountHolder loanHolder[BRANCH][HOLDER];

    cout<<"\n\n\tXYZ BANK LIMITED";
    cout<<"\n\t*************************";

    do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\t----------";
		cout<<"\n\n\t01. Input Account Holder Information";
		cout<<"\n\n\t02. Print Account Holder Information";
		cout<<"\n\n\t03. Withdraw";
		cout<<"\n\n\t04. Deposit";
		cout<<"\n\n\t05. Print Account Holder Information With Interest";
		cout<<"\n\n\t06. Branch Total";
		cout<<"\n\n\t07. Emlpoyee";
		cout<<"\n\n\t08. Withdraw Loan";
		cout<<"\n\n\t09. EXIT";
		cout<<"\n\n\tSelect Your Option (1-9) : ";
		cin>>choise;
		cout<<endl<<endl;

		switch(choise)
		{
		case 1:
			for (i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    account[i][j].setacNumber();
                    account[i][j].showacNumber();
                    account[i][j].inputname();
                    account[i][j].inputbalance();
                    cout<<endl<<endl;
                }
			break;

		case 2:
			for (i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    account[i][j].showacNumber();
                    account[i][j].showname();
                    cout<< account[i][j];
                    cout<<endl;
                }
            break;

		case 3:
			for(i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    account[i][j].showacNumber();
                    account[i][j].withdraw();
                    cout<<endl;
                }
			break;

		case 4:
			for(i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    account[i][j].showacNumber();
                    account[i][j].deposit();
                    cout<<endl;
                }
			break;

		case 5:
			for(i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    account[i][j].interest();
                    account[i][j].showacNumber();
                    account[i][j].showname();
                    account[i][j].showbalance();
                    cout<<endl;
                }
			break;

		case 6:
			for (i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    bra[i].calculateTotal(account[i][j].getbalance());
                }

            for (i=0;i<BRANCH;i++)
            {
                bra[i].showtotal();
                cout<<endl;
            }
			break;

		 case 7:
			for(i=0; i<BRANCH; i++)
            {
                actnt[i][0].calculateBonus(0,1,account,i,0.03);
                actnt[i][1].calculateBonus(1,2,account,i,0.03);
            }

            for (i=0;i<BRANCH;i++)
                for(k=0;k<2;k++)
                {
                    cout<<"\t\tBranch "<<i+1<<": "
                        <<"\tAccountant "<<k+1<<": ";
                    actnt[i][k].showbonus();
                    cout<<endl;
                }

            for (i=0;i<BRANCH;i++)
                {
                    m[i].calculateBonus(0,2,account,i,0.05);
                }

            for (i=0;i<BRANCH;i++)
            {
                cout<<"\t\tBranch "<<i+1<<": "<<"\tManager ";
                m[i].showbonus();
                cout<<endl;
            }

            own.calculateBonus(0,2,account,i,0.10);
            cout<<"\t\tOwner of the bank:\t";
            own.showbonus();
            cout<<endl;
			break;

        case 8:
			for (i=0;i<BRANCH;i++)
                for(j=0;j<HOLDER;j++)
                {
                    account[i][j].showacNumber();
                    loanHolder[i][j].withdrawLone();
                    loanHolder[i][j].showloan();
                    cout<<endl;
                }
			break;

        case 9:
			cout<<"\n\n\tThanks for using XYZ Bank management system softwere.";
			break;
		}
    }while(choise != 9);

    fflush(stdin);
    getchar();
    return 0;
}









