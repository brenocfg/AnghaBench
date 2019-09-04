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
struct policy_dbs_info {int rate_mult; struct dbs_data* dbs_data; } ;
struct od_policy_dbs_info {scalar_t__ freq_lo; } ;
struct od_dbs_tuners {scalar_t__ powersave_bias; } ;
struct dbs_data {unsigned int up_threshold; int sampling_down_factor; struct od_dbs_tuners* tuners; } ;
struct TYPE_3__ {unsigned int min_freq; unsigned int max_freq; } ;
struct cpufreq_policy {scalar_t__ cur; scalar_t__ max; TYPE_1__ cpuinfo; struct policy_dbs_info* governor_data; } ;
struct TYPE_4__ {unsigned int (* powersave_bias_target ) (struct cpufreq_policy*,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_RELATION_C ; 
 int /*<<< orphan*/  CPUFREQ_RELATION_L ; 
 int /*<<< orphan*/  __cpufreq_driver_target (struct cpufreq_policy*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbs_freq_increase (struct cpufreq_policy*,scalar_t__) ; 
 unsigned int dbs_update (struct cpufreq_policy*) ; 
 TYPE_2__ od_ops ; 
 unsigned int stub1 (struct cpufreq_policy*,unsigned int,int /*<<< orphan*/ ) ; 
 struct od_policy_dbs_info* to_dbs_info (struct policy_dbs_info*) ; 

__attribute__((used)) static void od_update(struct cpufreq_policy *policy)
{
	struct policy_dbs_info *policy_dbs = policy->governor_data;
	struct od_policy_dbs_info *dbs_info = to_dbs_info(policy_dbs);
	struct dbs_data *dbs_data = policy_dbs->dbs_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	unsigned int load = dbs_update(policy);

	dbs_info->freq_lo = 0;

	/* Check for frequency increase */
	if (load > dbs_data->up_threshold) {
		/* If switching to max speed, apply sampling_down_factor */
		if (policy->cur < policy->max)
			policy_dbs->rate_mult = dbs_data->sampling_down_factor;
		dbs_freq_increase(policy, policy->max);
	} else {
		/* Calculate the next frequency proportional to load */
		unsigned int freq_next, min_f, max_f;

		min_f = policy->cpuinfo.min_freq;
		max_f = policy->cpuinfo.max_freq;
		freq_next = min_f + load * (max_f - min_f) / 100;

		/* No longer fully busy, reset rate_mult */
		policy_dbs->rate_mult = 1;

		if (od_tuners->powersave_bias)
			freq_next = od_ops.powersave_bias_target(policy,
								 freq_next,
								 CPUFREQ_RELATION_L);

		__cpufreq_driver_target(policy, freq_next, CPUFREQ_RELATION_C);
	}
}