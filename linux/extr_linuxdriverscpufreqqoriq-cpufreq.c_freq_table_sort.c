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
struct cpufreq_frequency_table {unsigned int frequency; int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 unsigned int CPUFREQ_ENTRY_INVALID ; 

__attribute__((used)) static void freq_table_sort(struct cpufreq_frequency_table *freq_table,
		int count)
{
	int i, j, ind;
	unsigned int freq, max_freq;
	struct cpufreq_frequency_table table;

	for (i = 0; i < count - 1; i++) {
		max_freq = freq_table[i].frequency;
		ind = i;
		for (j = i + 1; j < count; j++) {
			freq = freq_table[j].frequency;
			if (freq == CPUFREQ_ENTRY_INVALID ||
					freq <= max_freq)
				continue;
			ind = j;
			max_freq = freq;
		}

		if (ind != i) {
			/* exchange the frequencies */
			table.driver_data = freq_table[i].driver_data;
			table.frequency = freq_table[i].frequency;
			freq_table[i].driver_data = freq_table[ind].driver_data;
			freq_table[i].frequency = freq_table[ind].frequency;
			freq_table[ind].driver_data = table.driver_data;
			freq_table[ind].frequency = table.frequency;
		}
	}
}