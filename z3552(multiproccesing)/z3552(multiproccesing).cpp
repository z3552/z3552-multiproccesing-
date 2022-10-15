#include <iostream>
#include <thread>
#include <string>
#include <vector>

void newRazm(int& Razm) {
    std::cout << "vvedite znachenie volue:";
    std::cin >> Razm;
    std::string out = "[newRazm] t0 new Razm: " + std::to_string(Razm) + " \n";
    std::cout << out;
}

class workClass {
public:
    void operator() () {
        std::string out = "[operator] t1 running\n";
        std::cout << out;
    };
};
int main() {
    std::cout << "Main thread running" << std::endl;
    std::vector<std::thread> detachPool;

    int Razm = 5;
    std::string Razm_out = "[main] \told Razm: " + std::to_string(Razm);
    std::thread t0(newRazm, std::ref(Razm));
    t0.join();
    Razm_out += "\tnew Razm: " + std::to_string(Razm) + "\n";
    std::cout << Razm_out;

    std::thread t1{ workClass() };
    detachPool.push_back(std::move(t1));

    std::thread t2([]() {
        std::string out = "[delta] t2 running\n";
        std::cout << out; });
    detachPool.push_back(std::move(t2));

    for (std::thread& t : detachPool) {
        t.detach();
    }
    std::string out = "Zavershenie potoka\n";
    std::cout << out;
    return 0;
}