#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class BankAccount {
public:
  BankAccount(int initial_balance = 0) : balance(initial_balance), mutex_() {}

  void deposit(int amount) {
    std::lock_guard<std::mutex> lock(mutex_);
    balance += amount;
  }

  int getBalance() const {
    return balance;
  }

private:
  int balance = 0;
  std::mutex mutex_;
};

void friendDeposit(BankAccount& account, int amount, int friendId) {
  
  std::cout << "Friend " << friendId << " depositing $" << amount << std::endl;
  account.deposit(amount);
  std::cout << "Friend " << friendId << " deposit completed. New balance: $" << account.getBalance() << std::endl;
}

int main() {

  BankAccount account(1000);
  std::cout<<"Initial Balance : "<<account.getBalance()<<"\n"<<std::endl;
  int deposit1 = 50;
  int deposit2 = 75;

  
  std::thread thread1(friendDeposit, std::ref(account), deposit1, 1);
  std::thread thread2(friendDeposit, std::ref(account), deposit2, 2);

  
  thread1.join();
  thread2.join();

  std::cout << "\n\nAll deposits completed." << std::endl;

  return 0;
}
