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
struct task_struct {int dummy; } ;

/* Variables and functions */
 unsigned int cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_csr (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_halt (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_cpu_out_of_reset (unsigned int) ; 
 int /*<<< orphan*/  tegra_enable_cpu_clock (unsigned int) ; 
 int /*<<< orphan*/  tegra_put_cpu_in_reset (unsigned int) ; 

__attribute__((used)) static int tegra20_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	cpu = cpu_logical_map(cpu);

	/*
	 * Force the CPU into reset. The CPU must remain in reset when
	 * the flow controller state is cleared (which will cause the
	 * flow controller to stop driving reset if the CPU has been
	 * power-gated via the flow controller). This will have no
	 * effect on first boot of the CPU since it should already be
	 * in reset.
	 */
	tegra_put_cpu_in_reset(cpu);

	/*
	 * Unhalt the CPU. If the flow controller was used to
	 * power-gate the CPU this will cause the flow controller to
	 * stop driving reset. The CPU will remain in reset because the
	 * clock and reset block is now driving reset.
	 */
	flowctrl_write_cpu_halt(cpu, 0);

	tegra_enable_cpu_clock(cpu);
	flowctrl_write_cpu_csr(cpu, 0); /* Clear flow controller CSR. */
	tegra_cpu_out_of_reset(cpu);
	return 0;
}