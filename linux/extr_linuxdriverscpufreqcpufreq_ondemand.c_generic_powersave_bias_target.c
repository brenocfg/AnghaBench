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
struct policy_dbs_info {struct dbs_data* dbs_data; } ;
struct od_policy_dbs_info {unsigned int freq_lo; unsigned int freq_lo_delay_us; unsigned int freq_hi_delay_us; } ;
struct od_dbs_tuners {unsigned int powersave_bias; } ;
struct dbs_data {unsigned int sampling_rate; struct od_dbs_tuners* tuners; } ;
struct cpufreq_policy {struct cpufreq_frequency_table* freq_table; struct policy_dbs_info* governor_data; } ;
struct cpufreq_frequency_table {unsigned int frequency; } ;

/* Variables and functions */
 unsigned int cpufreq_frequency_table_target (struct cpufreq_policy*,unsigned int,unsigned int) ; 
 unsigned int cpufreq_table_find_index_h (struct cpufreq_policy*,unsigned int) ; 
 unsigned int cpufreq_table_find_index_l (struct cpufreq_policy*,unsigned int) ; 
 struct od_policy_dbs_info* to_dbs_info (struct policy_dbs_info*) ; 

__attribute__((used)) static unsigned int generic_powersave_bias_target(struct cpufreq_policy *policy,
		unsigned int freq_next, unsigned int relation)
{
	unsigned int freq_req, freq_reduc, freq_avg;
	unsigned int freq_hi, freq_lo;
	unsigned int index;
	unsigned int delay_hi_us;
	struct policy_dbs_info *policy_dbs = policy->governor_data;
	struct od_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	struct dbs_data *dbs_data = policy_dbs->dbs_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	struct cpufreq_frequency_table *freq_table = policy->freq_table;

	if (!freq_table) {
		dbs_info->freq_lo = 0;
		dbs_info->freq_lo_delay_us = 0;
		return freq_next;
	}

	index = cpufreq_frequency_table_target(policy, freq_next, relation);
	freq_req = freq_table[index].frequency;
	freq_reduc = freq_req * od_tuners->powersave_bias / 1000;
	freq_avg = freq_req - freq_reduc;

	/* Find freq bounds for freq_avg in freq_table */
	index = cpufreq_table_find_index_h(policy, freq_avg);
	freq_lo = freq_table[index].frequency;
	index = cpufreq_table_find_index_l(policy, freq_avg);
	freq_hi = freq_table[index].frequency;

	/* Find out how long we have to be in hi and lo freqs */
	if (freq_hi == freq_lo) {
		dbs_info->freq_lo = 0;
		dbs_info->freq_lo_delay_us = 0;
		return freq_lo;
	}
	delay_hi_us = (freq_avg - freq_lo) * dbs_data->sampling_rate;
	delay_hi_us += (freq_hi - freq_lo) / 2;
	delay_hi_us /= freq_hi - freq_lo;
	dbs_info->freq_hi_delay_us = delay_hi_us;
	dbs_info->freq_lo = freq_lo;
	dbs_info->freq_lo_delay_us = dbs_data->sampling_rate - delay_hi_us;
	return freq_hi;
}