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
struct cpufreq_policy {size_t cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/ * all_cpu_data ; 
 int /*<<< orphan*/  intel_pstate_set_min_pstate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_cpufreq_stop_cpu(struct cpufreq_policy *policy)
{
	intel_pstate_set_min_pstate(all_cpu_data[policy->cpu]);
}