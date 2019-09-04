#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u64 ;
struct cppc_perf_caps {unsigned int lowest_freq; unsigned int nominal_freq; unsigned int nominal_perf; unsigned int lowest_perf; unsigned int highest_perf; } ;
struct cppc_cpudata {struct cppc_perf_caps perf_caps; } ;

/* Variables and functions */
 unsigned int cppc_get_dmi_max_khz () ; 

__attribute__((used)) static unsigned int cppc_cpufreq_perf_to_khz(struct cppc_cpudata *cpu,
					unsigned int perf)
{
	static u64 max_khz;
	struct cppc_perf_caps *caps = &cpu->perf_caps;
	u64 mul, div;

	if (caps->lowest_freq && caps->nominal_freq) {
		if (perf >= caps->nominal_perf) {
			mul = caps->nominal_freq;
			div = caps->nominal_perf;
		} else {
			mul = caps->nominal_freq - caps->lowest_freq;
			div = caps->nominal_perf - caps->lowest_perf;
		}
	} else {
		if (!max_khz)
			max_khz = cppc_get_dmi_max_khz();
		mul = max_khz;
		div = cpu->perf_caps.highest_perf;
	}
	return (u64)perf * mul / div;
}