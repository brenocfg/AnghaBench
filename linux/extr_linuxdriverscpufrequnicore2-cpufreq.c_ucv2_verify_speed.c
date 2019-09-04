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
struct cpufreq_policy {scalar_t__ cpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_verify_within_cpu_limits (struct cpufreq_policy*) ; 

__attribute__((used)) static int ucv2_verify_speed(struct cpufreq_policy *policy)
{
	if (policy->cpu)
		return -EINVAL;

	cpufreq_verify_within_cpu_limits(policy);
	return 0;
}