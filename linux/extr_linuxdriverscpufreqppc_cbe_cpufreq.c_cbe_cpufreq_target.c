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
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 TYPE_1__* cbe_freqs ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_pmode (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int cbe_cpufreq_target(struct cpufreq_policy *policy,
			      unsigned int cbe_pmode_new)
{
	pr_debug("setting frequency for cpu %d to %d kHz, " \
		 "1/%d of max frequency\n",
		 policy->cpu,
		 cbe_freqs[cbe_pmode_new].frequency,
		 cbe_freqs[cbe_pmode_new].driver_data);

	return set_pmode(policy->cpu, cbe_pmode_new);
}