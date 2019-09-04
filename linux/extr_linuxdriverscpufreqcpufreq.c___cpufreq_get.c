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
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  update; scalar_t__ fast_switch_enabled; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {unsigned int (* get ) (int /*<<< orphan*/ ) ;int flags; } ;

/* Variables and functions */
 int CPUFREQ_CONST_LOOPS ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_out_of_sync (struct cpufreq_policy*,unsigned int) ; 
 int policy_is_inactive (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int __cpufreq_get(struct cpufreq_policy *policy)
{
	unsigned int ret_freq = 0;

	if (unlikely(policy_is_inactive(policy)) || !cpufreq_driver->get)
		return ret_freq;

	ret_freq = cpufreq_driver->get(policy->cpu);

	/*
	 * If fast frequency switching is used with the given policy, the check
	 * against policy->cur is pointless, so skip it in that case too.
	 */
	if (policy->fast_switch_enabled)
		return ret_freq;

	if (ret_freq && policy->cur &&
		!(cpufreq_driver->flags & CPUFREQ_CONST_LOOPS)) {
		/* verify no discrepancy between actual and
					saved value exists */
		if (unlikely(ret_freq != policy->cur)) {
			cpufreq_out_of_sync(policy, ret_freq);
			schedule_work(&policy->update);
		}
	}

	return ret_freq;
}