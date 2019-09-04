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
struct TYPE_2__ {int /*<<< orphan*/  max_freq; } ;
struct cpufreq_policy {size_t cpu; scalar_t__ policy; int /*<<< orphan*/  max; TYPE_1__ cpuinfo; } ;
struct cpudata {scalar_t__ policy; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_POLICY_PERFORMANCE ; 
 int ENODEV ; 
 struct cpudata** all_cpu_data ; 
 scalar_t__ hwp_active ; 
 int /*<<< orphan*/  hwp_boost ; 
 int /*<<< orphan*/  intel_pstate_clear_update_util_hook (size_t) ; 
 int /*<<< orphan*/  intel_pstate_hwp_set (size_t) ; 
 int /*<<< orphan*/  intel_pstate_limits_lock ; 
 int /*<<< orphan*/  intel_pstate_max_within_limits (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_set_update_util_hook (size_t) ; 
 int /*<<< orphan*/  intel_pstate_update_perf_limits (struct cpufreq_policy*,struct cpudata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pstate_set_policy(struct cpufreq_policy *policy)
{
	struct cpudata *cpu;

	if (!policy->cpuinfo.max_freq)
		return -ENODEV;

	pr_debug("set_policy cpuinfo.max %u policy->max %u\n",
		 policy->cpuinfo.max_freq, policy->max);

	cpu = all_cpu_data[policy->cpu];
	cpu->policy = policy->policy;

	mutex_lock(&intel_pstate_limits_lock);

	intel_pstate_update_perf_limits(policy, cpu);

	if (cpu->policy == CPUFREQ_POLICY_PERFORMANCE) {
		/*
		 * NOHZ_FULL CPUs need this as the governor callback may not
		 * be invoked on them.
		 */
		intel_pstate_clear_update_util_hook(policy->cpu);
		intel_pstate_max_within_limits(cpu);
	} else {
		intel_pstate_set_update_util_hook(policy->cpu);
	}

	if (hwp_active) {
		/*
		 * When hwp_boost was active before and dynamically it
		 * was turned off, in that case we need to clear the
		 * update util hook.
		 */
		if (!hwp_boost)
			intel_pstate_clear_update_util_hook(policy->cpu);
		intel_pstate_hwp_set(policy->cpu);
	}

	mutex_unlock(&intel_pstate_limits_lock);

	return 0;
}