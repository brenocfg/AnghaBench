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

__attribute__((used)) static unsigned int cppc_cpufreq_khz_to_perf(struct cppc_cpudata *cpu,
					unsigned int freq)
{
	static u64 max_khz;
	struct cppc_perf_caps *caps = &cpu->perf_caps;
	u64  mul, div;

	if (caps->lowest_freq && caps->nominal_freq) {
		if (freq >= caps->nominal_freq) {
			mul = caps->nominal_perf;
			div = caps->nominal_freq;
		} else {
			mul = caps->lowest_perf;
			div = caps->lowest_freq;
		}
	} else {
		if (!max_khz)
			max_khz = cppc_get_dmi_max_khz();
		mul = cpu->perf_caps.highest_perf;
		div = max_khz;
	}

	return (u64)freq * mul / div;
}