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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct cpufreq_policy* cpufreq_cpu_get (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  memcpy (struct cpufreq_policy*,struct cpufreq_policy*,int) ; 

int cpufreq_get_policy(struct cpufreq_policy *policy, unsigned int cpu)
{
	struct cpufreq_policy *cpu_policy;
	if (!policy)
		return -EINVAL;

	cpu_policy = cpufreq_cpu_get(cpu);
	if (!cpu_policy)
		return -EINVAL;

	memcpy(policy, cpu_policy, sizeof(*policy));

	cpufreq_cpu_put(cpu_policy);
	return 0;
}