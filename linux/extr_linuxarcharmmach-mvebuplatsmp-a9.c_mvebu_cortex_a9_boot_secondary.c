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
 int /*<<< orphan*/  arch_send_wakeup_ipi_mask (int /*<<< orphan*/ ) ; 
 int cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  mvebu_cortex_a9_secondary_startup ; 
 int mvebu_cpu_reset_deassert (int) ; 
 int /*<<< orphan*/  mvebu_pmsu_set_cpu_boot_addr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_system_controller_set_cpu_boot_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int mvebu_cortex_a9_boot_secondary(unsigned int cpu,
						    struct task_struct *idle)
{
	int ret, hw_cpu;

	pr_info("Booting CPU %d\n", cpu);

	/*
	 * Write the address of secondary startup into the system-wide
	 * flags register. The boot monitor waits until it receives a
	 * soft interrupt, and then the secondary CPU branches to this
	 * address.
	 */
	hw_cpu = cpu_logical_map(cpu);
	if (of_machine_is_compatible("marvell,armada375"))
		mvebu_system_controller_set_cpu_boot_addr(mvebu_cortex_a9_secondary_startup);
	else
		mvebu_pmsu_set_cpu_boot_addr(hw_cpu, mvebu_cortex_a9_secondary_startup);
	smp_wmb();

	/*
	 * Doing this before deasserting the CPUs is needed to wake up CPUs
	 * in the offline state after using CPU hotplug.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	ret = mvebu_cpu_reset_deassert(hw_cpu);
	if (ret) {
		pr_err("Could not start the secondary CPU: %d\n", ret);
		return ret;
	}

	return 0;
}