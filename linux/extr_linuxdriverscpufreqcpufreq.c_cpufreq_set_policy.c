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
struct cpufreq_policy {scalar_t__ min; scalar_t__ max; struct cpufreq_governor* governor; int /*<<< orphan*/  policy; int /*<<< orphan*/  cached_target_freq; int /*<<< orphan*/  cpuinfo; int /*<<< orphan*/  cpu; } ;
struct cpufreq_governor {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int (* verify ) (struct cpufreq_policy*) ;int (* setpolicy ) (struct cpufreq_policy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_ADJUST ; 
 int /*<<< orphan*/  CPUFREQ_NOTIFY ; 
 int EINVAL ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cpufreq_policy*) ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_exit_governor (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_governor_limits (struct cpufreq_policy*) ; 
 int cpufreq_init_governor (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_policy_notifier_list ; 
 int cpufreq_start_governor (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpufreq_stop_governor (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int stub1 (struct cpufreq_policy*) ; 
 int stub2 (struct cpufreq_policy*) ; 
 int stub3 (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  trace_cpu_frequency_limits (struct cpufreq_policy*) ; 

__attribute__((used)) static int cpufreq_set_policy(struct cpufreq_policy *policy,
				struct cpufreq_policy *new_policy)
{
	struct cpufreq_governor *old_gov;
	int ret;

	pr_debug("setting new policy for CPU %u: %u - %u kHz\n",
		 new_policy->cpu, new_policy->min, new_policy->max);

	memcpy(&new_policy->cpuinfo, &policy->cpuinfo, sizeof(policy->cpuinfo));

	/*
	* This check works well when we store new min/max freq attributes,
	* because new_policy is a copy of policy with one field updated.
	*/
	if (new_policy->min > new_policy->max)
		return -EINVAL;

	/* verify the cpu speed can be set within this limit */
	ret = cpufreq_driver->verify(new_policy);
	if (ret)
		return ret;

	/* adjust if necessary - all reasons */
	blocking_notifier_call_chain(&cpufreq_policy_notifier_list,
			CPUFREQ_ADJUST, new_policy);

	/*
	 * verify the cpu speed can be set within this limit, which might be
	 * different to the first one
	 */
	ret = cpufreq_driver->verify(new_policy);
	if (ret)
		return ret;

	/* notification of the new policy */
	blocking_notifier_call_chain(&cpufreq_policy_notifier_list,
			CPUFREQ_NOTIFY, new_policy);

	policy->min = new_policy->min;
	policy->max = new_policy->max;
	trace_cpu_frequency_limits(policy);

	policy->cached_target_freq = UINT_MAX;

	pr_debug("new min and max freqs are %u - %u kHz\n",
		 policy->min, policy->max);

	if (cpufreq_driver->setpolicy) {
		policy->policy = new_policy->policy;
		pr_debug("setting range\n");
		return cpufreq_driver->setpolicy(new_policy);
	}

	if (new_policy->governor == policy->governor) {
		pr_debug("cpufreq: governor limits update\n");
		cpufreq_governor_limits(policy);
		return 0;
	}

	pr_debug("governor switch\n");

	/* save old, working values */
	old_gov = policy->governor;
	/* end old governor */
	if (old_gov) {
		cpufreq_stop_governor(policy);
		cpufreq_exit_governor(policy);
	}

	/* start new governor */
	policy->governor = new_policy->governor;
	ret = cpufreq_init_governor(policy);
	if (!ret) {
		ret = cpufreq_start_governor(policy);
		if (!ret) {
			pr_debug("cpufreq: governor change\n");
			return 0;
		}
		cpufreq_exit_governor(policy);
	}

	/* new governor failed, so re-start old one */
	pr_debug("starting governor %s failed\n", policy->governor->name);
	if (old_gov) {
		policy->governor = old_gov;
		if (cpufreq_init_governor(policy))
			policy->governor = NULL;
		else
			cpufreq_start_governor(policy);
	}

	return ret;
}