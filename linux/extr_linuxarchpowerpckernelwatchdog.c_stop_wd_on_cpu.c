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
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  stop_watchdog_timer_on (unsigned int) ; 
 int /*<<< orphan*/  wd_cpus_enabled ; 
 int /*<<< orphan*/  wd_smp_clear_cpu_pending (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd_smp_lock (unsigned long*) ; 
 int /*<<< orphan*/  wd_smp_unlock (unsigned long*) ; 

__attribute__((used)) static int stop_wd_on_cpu(unsigned int cpu)
{
	unsigned long flags;

	if (!cpumask_test_cpu(cpu, &wd_cpus_enabled))
		return 0; /* Can happen in CPU unplug case */

	stop_watchdog_timer_on(cpu);

	wd_smp_lock(&flags);
	cpumask_clear_cpu(cpu, &wd_cpus_enabled);
	wd_smp_unlock(&flags);

	wd_smp_clear_cpu_pending(cpu, get_tb());

	return 0;
}