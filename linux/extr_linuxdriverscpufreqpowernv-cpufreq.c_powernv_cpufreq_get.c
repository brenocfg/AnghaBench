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
struct powernv_smp_call_data {unsigned int freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_sibling_mask (unsigned int) ; 
 int /*<<< orphan*/  powernv_read_cpu_freq ; 
 int /*<<< orphan*/  smp_call_function_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct powernv_smp_call_data*,int) ; 

__attribute__((used)) static unsigned int powernv_cpufreq_get(unsigned int cpu)
{
	struct powernv_smp_call_data freq_data;

	smp_call_function_any(cpu_sibling_mask(cpu), powernv_read_cpu_freq,
			&freq_data, 1);

	return freq_data.freq;
}