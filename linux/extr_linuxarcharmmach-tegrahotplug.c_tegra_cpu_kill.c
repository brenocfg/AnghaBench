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
 unsigned int cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  tegra_disable_cpu_clock (unsigned int) ; 
 int /*<<< orphan*/  tegra_wait_cpu_in_reset (unsigned int) ; 

int tegra_cpu_kill(unsigned cpu)
{
	cpu = cpu_logical_map(cpu);

	/* Clock gate the CPU */
	tegra_wait_cpu_in_reset(cpu);
	tegra_disable_cpu_clock(cpu);

	return 1;
}