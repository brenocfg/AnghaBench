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
struct cpufreq_frequency_table {unsigned long frequency; } ;
struct clk_rate_round_data {struct cpufreq_frequency_table* arg; } ;

/* Variables and functions */
 unsigned long CPUFREQ_ENTRY_INVALID ; 

__attribute__((used)) static long clk_rate_table_iter(unsigned int pos,
				struct clk_rate_round_data *rounder)
{
	struct cpufreq_frequency_table *freq_table = rounder->arg;
	unsigned long freq = freq_table[pos].frequency;

	if (freq == CPUFREQ_ENTRY_INVALID)
		freq = 0;

	return freq;
}