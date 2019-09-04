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
struct cpufreq_policy {int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_RELATION_L ; 
 int /*<<< orphan*/  __cpufreq_driver_target (struct cpufreq_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpufreq_gov_powersave_limits(struct cpufreq_policy *policy)
{
	pr_debug("setting to %u kHz\n", policy->min);
	__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
}