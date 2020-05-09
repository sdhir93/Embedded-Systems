/*

FunctionTimer : Profiler class that saves the duration
spent in a particular function and reports results in a
minimal performance intrusive way

- Idea is to initialize start time on function entry
and calcualte duration on exit

- A static map is required that maps function name strings to
duration in milliseconds

- A static function report that prints out results

*/

typedef std::chrono::high_resolution_clock Time_t;

class FunctionTimer
{
private:
    std::string functionName; // Name of the function
    Time_t startTime;         // Time when entered a function
    static std::map<std::string, Time_t> mFunctionTimes; // Static map to hold function name string and corresponding durations

    // Constructor using initializer list
    FunctionTimer(string name) : functionName(name), startTime(Time_t::now())
    {
    }

    // Destructor called on exit of function
    ~FunctionTimer()
    {
        // Caclulate duration on exit
        auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(Time_t::now() - startTime);

        // Update the map
        mFunctionTimes[functionName] += durationMs;
    }

    static void report()
    {
        // Go over all the entries
        for(auto entry : mFunctionTimes)
        {
            // Get the funciton name and duration
            auto functionNameString = entry.first;
            auto duration = entry.second;

            // Print the duration
            cout << functionNameString << " ran for total duration of " << duration << " milliseconds" << endl;
        }
    }
};

// Sample usage
void myFunc()
{
    FunctionTimer ft("myfunc");
    // Do tasks
}


int main(int argc, char* argv[])
{
    // Call functions myFunc()
    FunctionTimer::report();
}