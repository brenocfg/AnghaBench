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
struct cpufreq_policy {int max; unsigned int min; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_verify_within_cpu_limits (struct cpufreq_policy*) ; 
 int fid ; 

__attribute__((used)) static int nforce2_verify(struct cpufreq_policy *policy)
{
	unsigned int fsb_pol_max;

	fsb_pol_max = policy->max / (fid * 100);

	if (policy->min < (fsb_pol_max * fid * 100))
		policy->max = (fsb_pol_max + 1) * fid * 100;

	cpufreq_verify_within_cpu_limits(policy);
	return 0;
}