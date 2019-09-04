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
struct cpufreq_policy {unsigned int* governor_data; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_RELATION_L ; 
 int EINVAL ; 
 int __cpufreq_driver_target (struct cpufreq_policy*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_managed ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  userspace_mutex ; 

__attribute__((used)) static int cpufreq_set(struct cpufreq_policy *policy, unsigned int freq)
{
	int ret = -EINVAL;
	unsigned int *setspeed = policy->governor_data;

	pr_debug("cpufreq_set for cpu %u, freq %u kHz\n", policy->cpu, freq);

	mutex_lock(&userspace_mutex);
	if (!per_cpu(cpu_is_managed, policy->cpu))
		goto err;

	*setspeed = freq;

	ret = __cpufreq_driver_target(policy, freq, CPUFREQ_RELATION_L);
 err:
	mutex_unlock(&userspace_mutex);
	return ret;
}