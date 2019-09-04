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
struct cpufreq_policy {TYPE_1__* freq_table; struct acpi_cpufreq_data* driver_data; } ;
struct acpi_cpufreq_data {int resume; } ;
struct TYPE_4__ {size_t state; } ;
struct TYPE_3__ {unsigned int frequency; } ;

/* Variables and functions */
 struct cpufreq_policy* cpufreq_cpu_get_raw (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 unsigned int extract_freq (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cur_val (int /*<<< orphan*/ ,struct acpi_cpufreq_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 TYPE_2__* to_perf_data (struct acpi_cpufreq_data*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int get_cur_freq_on_cpu(unsigned int cpu)
{
	struct acpi_cpufreq_data *data;
	struct cpufreq_policy *policy;
	unsigned int freq;
	unsigned int cached_freq;

	pr_debug("get_cur_freq_on_cpu (%d)\n", cpu);

	policy = cpufreq_cpu_get_raw(cpu);
	if (unlikely(!policy))
		return 0;

	data = policy->driver_data;
	if (unlikely(!data || !policy->freq_table))
		return 0;

	cached_freq = policy->freq_table[to_perf_data(data)->state].frequency;
	freq = extract_freq(policy, get_cur_val(cpumask_of(cpu), data));
	if (freq != cached_freq) {
		/*
		 * The dreaded BIOS frequency change behind our back.
		 * Force set the frequency on next target call.
		 */
		data->resume = 1;
	}

	pr_debug("cur freq = %u\n", freq);

	return freq;
}