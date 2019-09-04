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

__attribute__((used)) static void wait_for_master_cpu(int cpu)
{
#ifdef CONFIG_SMP
	/*
	 * wait for ACK from master CPU before continuing
	 * with AP initialization
	 */
	WARN_ON(cpumask_test_and_set_cpu(cpu, cpu_initialized_mask));
	while (!cpumask_test_cpu(cpu, cpu_callout_mask))
		cpu_relax();
#endif
}