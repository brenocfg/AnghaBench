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
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  cpu_enter_lowpower () ; 
 int /*<<< orphan*/  imx_set_cpu_arg (unsigned int,int /*<<< orphan*/ ) ; 

void imx_cpu_die(unsigned int cpu)
{
	cpu_enter_lowpower();
	/*
	 * We use the cpu jumping argument register to sync with
	 * imx_cpu_kill() which is running on cpu0 and waiting for
	 * the register being cleared to kill the cpu.
	 */
	imx_set_cpu_arg(cpu, ~0);

	while (1)
		cpu_do_idle();
}