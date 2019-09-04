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
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {unsigned int (* get ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_out_of_sync (struct cpufreq_policy*,unsigned int) ; 
 scalar_t__ has_target () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int cpufreq_update_current_freq(struct cpufreq_policy *policy)
{
	unsigned int new_freq;

	new_freq = cpufreq_driver->get(policy->cpu);
	if (!new_freq)
		return 0;

	if (!policy->cur) {
		pr_debug("cpufreq: Driver did not initialize current freq\n");
		policy->cur = new_freq;
	} else if (policy->cur != new_freq && has_target()) {
		cpufreq_out_of_sync(policy, new_freq);
	}

	return new_freq;
}