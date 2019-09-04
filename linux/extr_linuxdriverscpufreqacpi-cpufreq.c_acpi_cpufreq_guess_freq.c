#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_processor_performance {int state_count; unsigned int state; TYPE_1__* states; } ;
struct acpi_cpufreq_data {int dummy; } ;
struct TYPE_2__ {int core_frequency; } ;

/* Variables and functions */
 int cpu_khz ; 
 struct acpi_processor_performance* to_perf_data (struct acpi_cpufreq_data*) ; 

__attribute__((used)) static unsigned long
acpi_cpufreq_guess_freq(struct acpi_cpufreq_data *data, unsigned int cpu)
{
	struct acpi_processor_performance *perf;

	perf = to_perf_data(data);
	if (cpu_khz) {
		/* search the closest match to cpu_khz */
		unsigned int i;
		unsigned long freq;
		unsigned long freqn = perf->states[0].core_frequency * 1000;

		for (i = 0; i < (perf->state_count-1); i++) {
			freq = freqn;
			freqn = perf->states[i+1].core_frequency * 1000;
			if ((2 * cpu_khz) > (freqn + freq)) {
				perf->state = i;
				return freq;
			}
		}
		perf->state = perf->state_count-1;
		return freqn;
	} else {
		/* assume CPU is at P0... */
		perf->state = 0;
		return perf->states[0].core_frequency * 1000;
	}
}