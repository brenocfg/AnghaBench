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
struct TYPE_3__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct cpufreq_policy {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  cur; TYPE_1__ user_policy; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {int /*<<< orphan*/  setpolicy; scalar_t__ get; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct cpufreq_policy* cpufreq_cpu_get (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 TYPE_2__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_set_policy (struct cpufreq_policy*,struct cpufreq_policy*) ; 
 scalar_t__ cpufreq_suspended ; 
 int /*<<< orphan*/  cpufreq_update_current_freq (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct cpufreq_policy*,struct cpufreq_policy*,int) ; 
 scalar_t__ policy_is_inactive (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void cpufreq_update_policy(unsigned int cpu)
{
	struct cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	struct cpufreq_policy new_policy;

	if (!policy)
		return;

	down_write(&policy->rwsem);

	if (policy_is_inactive(policy))
		goto unlock;

	pr_debug("updating policy for CPU %u\n", cpu);
	memcpy(&new_policy, policy, sizeof(*policy));
	new_policy.min = policy->user_policy.min;
	new_policy.max = policy->user_policy.max;

	/*
	 * BIOS might change freq behind our back
	 * -> ask driver for current freq and notify governors about a change
	 */
	if (cpufreq_driver->get && !cpufreq_driver->setpolicy) {
		if (cpufreq_suspended)
			goto unlock;

		new_policy.cur = cpufreq_update_current_freq(policy);
		if (WARN_ON(!new_policy.cur))
			goto unlock;
	}

	cpufreq_set_policy(policy, &new_policy);

unlock:
	up_write(&policy->rwsem);

	cpufreq_cpu_put(policy);
}