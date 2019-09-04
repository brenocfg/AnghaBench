#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; TYPE_1__* freq_table; } ;
struct TYPE_4__ {scalar_t__ ctrl_val; } ;
struct TYPE_3__ {unsigned int driver_data; } ;

/* Variables and functions */
 int INTEL_PERF_CTL_MASK ; 
 int /*<<< orphan*/  MSR_IA32_PERF_CTL ; 
 int /*<<< orphan*/  rdmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_2__* sfi_cpufreq_array ; 
 int /*<<< orphan*/  wrmsr_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sfi_cpufreq_target(struct cpufreq_policy *policy, unsigned int index)
{
	unsigned int next_perf_state = 0; /* Index into perf table */
	u32 lo, hi;

	next_perf_state = policy->freq_table[index].driver_data;

	rdmsr_on_cpu(policy->cpu, MSR_IA32_PERF_CTL, &lo, &hi);
	lo = (lo & ~INTEL_PERF_CTL_MASK) |
		((u32) sfi_cpufreq_array[next_perf_state].ctrl_val &
		INTEL_PERF_CTL_MASK);
	wrmsr_on_cpu(policy->cpu, MSR_IA32_PERF_CTL, lo, hi);

	return 0;
}