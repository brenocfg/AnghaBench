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
struct cpufreq_frequency_table {scalar_t__ frequency; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_ENTRY_INVALID ; 

__attribute__((used)) static void freq_table_redup(struct cpufreq_frequency_table *freq_table,
		int count)
{
	int i, j;

	for (i = 1; i < count; i++) {
		for (j = 0; j < i; j++) {
			if (freq_table[j].frequency == CPUFREQ_ENTRY_INVALID ||
					freq_table[j].frequency !=
					freq_table[i].frequency)
				continue;

			freq_table[i].frequency = CPUFREQ_ENTRY_INVALID;
			break;
		}
	}
}