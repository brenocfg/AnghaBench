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
struct cpufreq_policy {unsigned int cur; unsigned int restore_freq; int /*<<< orphan*/  cpu; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_2__ {int (* target ) (struct cpufreq_policy*,unsigned int,unsigned int) ;int /*<<< orphan*/  target_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int __target_index (struct cpufreq_policy*,int) ; 
 unsigned int clamp_val (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpufreq_disabled () ; 
 TYPE_1__* cpufreq_driver ; 
 int cpufreq_frequency_table_target (struct cpufreq_policy*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int stub1 (struct cpufreq_policy*,unsigned int,unsigned int) ; 

int __cpufreq_driver_target(struct cpufreq_policy *policy,
			    unsigned int target_freq,
			    unsigned int relation)
{
	unsigned int old_target_freq = target_freq;
	int index;

	if (cpufreq_disabled())
		return -ENODEV;

	/* Make sure that target_freq is within supported range */
	target_freq = clamp_val(target_freq, policy->min, policy->max);

	pr_debug("target for CPU %u: %u kHz, relation %u, requested %u kHz\n",
		 policy->cpu, target_freq, relation, old_target_freq);

	/*
	 * This might look like a redundant call as we are checking it again
	 * after finding index. But it is left intentionally for cases where
	 * exactly same freq is called again and so we can save on few function
	 * calls.
	 */
	if (target_freq == policy->cur)
		return 0;

	/* Save last value to restore later on errors */
	policy->restore_freq = policy->cur;

	if (cpufreq_driver->target)
		return cpufreq_driver->target(policy, target_freq, relation);

	if (!cpufreq_driver->target_index)
		return -EINVAL;

	index = cpufreq_frequency_table_target(policy, target_freq, relation);

	return __target_index(policy, index);
}