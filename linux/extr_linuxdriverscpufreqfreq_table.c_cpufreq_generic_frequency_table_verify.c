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
struct cpufreq_policy {int /*<<< orphan*/  freq_table; } ;

/* Variables and functions */
 int ENODEV ; 
 int cpufreq_frequency_table_verify (struct cpufreq_policy*,int /*<<< orphan*/ ) ; 

int cpufreq_generic_frequency_table_verify(struct cpufreq_policy *policy)
{
	if (!policy->freq_table)
		return -ENODEV;

	return cpufreq_frequency_table_verify(policy, policy->freq_table);
}