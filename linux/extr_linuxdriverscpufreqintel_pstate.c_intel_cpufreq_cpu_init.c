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
struct TYPE_2__ {int /*<<< orphan*/  min_freq; int /*<<< orphan*/  transition_latency; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; int /*<<< orphan*/  cur; int /*<<< orphan*/  transition_delay_us; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_CPUFREQ_TRANSITION_DELAY ; 
 int /*<<< orphan*/  INTEL_CPUFREQ_TRANSITION_LATENCY ; 
 int __intel_pstate_cpu_init (struct cpufreq_policy*) ; 

__attribute__((used)) static int intel_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	int ret = __intel_pstate_cpu_init(policy);

	if (ret)
		return ret;

	policy->cpuinfo.transition_latency = INTEL_CPUFREQ_TRANSITION_LATENCY;
	policy->transition_delay_us = INTEL_CPUFREQ_TRANSITION_DELAY;
	/* This reflects the intel_pstate_get_cpu_pstates() setting. */
	policy->cur = policy->cpuinfo.min_freq;

	return 0;
}