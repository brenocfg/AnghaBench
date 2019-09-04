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
struct cpufreq_policy {unsigned int cached_target_freq; unsigned int cached_resolved_idx; struct cpufreq_frequency_table* freq_table; struct acpi_cpufreq_data* driver_data; } ;
struct cpufreq_frequency_table {unsigned int frequency; unsigned int driver_data; } ;
struct acpi_processor_performance {unsigned int state; TYPE_1__* states; int /*<<< orphan*/  control_register; } ;
struct acpi_cpufreq_data {int /*<<< orphan*/  (* cpu_freq_write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ resume; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 unsigned int cpufreq_table_find_index_dl (struct cpufreq_policy*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct acpi_processor_performance* to_perf_data (struct acpi_cpufreq_data*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static unsigned int acpi_cpufreq_fast_switch(struct cpufreq_policy *policy,
					     unsigned int target_freq)
{
	struct acpi_cpufreq_data *data = policy->driver_data;
	struct acpi_processor_performance *perf;
	struct cpufreq_frequency_table *entry;
	unsigned int next_perf_state, next_freq, index;

	/*
	 * Find the closest frequency above target_freq.
	 */
	if (policy->cached_target_freq == target_freq)
		index = policy->cached_resolved_idx;
	else
		index = cpufreq_table_find_index_dl(policy, target_freq);

	entry = &policy->freq_table[index];
	next_freq = entry->frequency;
	next_perf_state = entry->driver_data;

	perf = to_perf_data(data);
	if (perf->state == next_perf_state) {
		if (unlikely(data->resume))
			data->resume = 0;
		else
			return next_freq;
	}

	data->cpu_freq_write(&perf->control_register,
			     perf->states[next_perf_state].control);
	perf->state = next_perf_state;
	return next_freq;
}