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
struct cpufreq_policy {unsigned int* governor_data; unsigned int min; unsigned int max; int /*<<< orphan*/  cur; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_RELATION_H ; 
 int /*<<< orphan*/  CPUFREQ_RELATION_L ; 
 int /*<<< orphan*/  __cpufreq_driver_target (struct cpufreq_policy*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  userspace_mutex ; 

__attribute__((used)) static void cpufreq_userspace_policy_limits(struct cpufreq_policy *policy)
{
	unsigned int *setspeed = policy->governor_data;

	mutex_lock(&userspace_mutex);

	pr_debug("limit event for cpu %u: %u - %u kHz, currently %u kHz, last set to %u kHz\n",
		 policy->cpu, policy->min, policy->max, policy->cur, *setspeed);

	if (policy->max < *setspeed)
		__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
	else if (policy->min > *setspeed)
		__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
	else
		__cpufreq_driver_target(policy, *setspeed, CPUFREQ_RELATION_L);

	mutex_unlock(&userspace_mutex);
}