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

/* Variables and functions */
 int NMI_WATCHDOG_ENABLED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int cpumask_weight (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  start_watchdog_timer_on (unsigned int) ; 
 int /*<<< orphan*/  watchdog_cpumask ; 
 int watchdog_enabled ; 
 int /*<<< orphan*/  wd_cpus_enabled ; 
 int /*<<< orphan*/  wd_smp_cpus_pending ; 
 int /*<<< orphan*/  wd_smp_last_reset_tb ; 
 int /*<<< orphan*/  wd_smp_lock (unsigned long*) ; 
 int /*<<< orphan*/  wd_smp_unlock (unsigned long*) ; 

__attribute__((used)) static int start_wd_on_cpu(unsigned int cpu)
{
	unsigned long flags;

	if (cpumask_test_cpu(cpu, &wd_cpus_enabled)) {
		WARN_ON(1);
		return 0;
	}

	if (!(watchdog_enabled & NMI_WATCHDOG_ENABLED))
		return 0;

	if (!cpumask_test_cpu(cpu, &watchdog_cpumask))
		return 0;

	wd_smp_lock(&flags);
	cpumask_set_cpu(cpu, &wd_cpus_enabled);
	if (cpumask_weight(&wd_cpus_enabled) == 1) {
		cpumask_set_cpu(cpu, &wd_smp_cpus_pending);
		wd_smp_last_reset_tb = get_tb();
	}
	wd_smp_unlock(&flags);

	start_watchdog_timer_on(cpu);

	return 0;
}