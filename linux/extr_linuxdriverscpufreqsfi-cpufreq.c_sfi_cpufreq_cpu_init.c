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
struct TYPE_2__ {int transition_latency; } ;
struct cpufreq_policy {int /*<<< orphan*/  freq_table; TYPE_1__ cpuinfo; int /*<<< orphan*/  shared_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_SHARED_TYPE_HW ; 
 int /*<<< orphan*/  freq_table ; 

__attribute__((used)) static int sfi_cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	policy->shared_type = CPUFREQ_SHARED_TYPE_HW;
	policy->cpuinfo.transition_latency = 100000;	/* 100us */
	policy->freq_table = freq_table;

	return 0;
}