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
struct policy_dbs_info {scalar_t__ sample_delay_ns; unsigned int rate_mult; struct dbs_data* dbs_data; } ;
struct od_policy_dbs_info {int sample_type; unsigned int freq_lo_delay_us; unsigned int freq_hi_delay_us; scalar_t__ freq_lo; } ;
struct dbs_data {unsigned int sampling_rate; } ;
struct cpufreq_policy {struct policy_dbs_info* governor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_RELATION_H ; 
 int OD_NORMAL_SAMPLE ; 
 int OD_SUB_SAMPLE ; 
 int /*<<< orphan*/  __cpufreq_driver_target (struct cpufreq_policy*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  od_update (struct cpufreq_policy*) ; 
 struct od_policy_dbs_info* to_dbs_info (struct policy_dbs_info*) ; 

__attribute__((used)) static unsigned int od_dbs_update(struct cpufreq_policy *policy)
{
	struct policy_dbs_info *policy_dbs = policy->governor_data;
	struct dbs_data *dbs_data = policy_dbs->dbs_data;
	struct od_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	int sample_type = dbs_info->sample_type;

	/* Common NORMAL_SAMPLE setup */
	dbs_info->sample_type = OD_NORMAL_SAMPLE;
	/*
	 * OD_SUB_SAMPLE doesn't make sense if sample_delay_ns is 0, so ignore
	 * it then.
	 */
	if (sample_type == OD_SUB_SAMPLE && policy_dbs->sample_delay_ns > 0) {
		__cpufreq_driver_target(policy, dbs_info->freq_lo,
					CPUFREQ_RELATION_H);
		return dbs_info->freq_lo_delay_us;
	}

	od_update(policy);

	if (dbs_info->freq_lo) {
		/* Setup SUB_SAMPLE */
		dbs_info->sample_type = OD_SUB_SAMPLE;
		return dbs_info->freq_hi_delay_us;
	}

	return dbs_data->sampling_rate * policy_dbs->rate_mult;
}