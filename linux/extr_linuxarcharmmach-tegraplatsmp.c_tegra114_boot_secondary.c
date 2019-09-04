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
 int FLOW_CTRL_SCLK_RESUME ; 
 int FLOW_CTRL_WAITEVENT ; 
 unsigned int cpu_logical_map (unsigned int) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_csr (unsigned int,int) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_halt (unsigned int,int) ; 
 int /*<<< orphan*/  tegra_cpu_init_mask ; 
 int tegra_pmc_cpu_power_on (unsigned int) ; 

__attribute__((used)) static int tegra114_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	int ret = 0;

	cpu = cpu_logical_map(cpu);

	if (cpumask_test_cpu(cpu, &tegra_cpu_init_mask)) {
		/*
		 * Warm boot flow
		 * The flow controller in charge of the power state and
		 * control for each CPU.
		 */
		/* set SCLK as event trigger for flow controller */
		flowctrl_write_cpu_csr(cpu, 1);
		flowctrl_write_cpu_halt(cpu,
				FLOW_CTRL_WAITEVENT | FLOW_CTRL_SCLK_RESUME);
	} else {
		/*
		 * Cold boot flow
		 * The CPU is powered up by toggling PMC directly. It will
		 * also initial power state in flow controller. After that,
		 * the CPU's power state is maintained by flow controller.
		 */
		ret = tegra_pmc_cpu_power_on(cpu);
	}

	return ret;
}