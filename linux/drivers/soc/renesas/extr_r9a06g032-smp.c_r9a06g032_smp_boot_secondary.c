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
 int ENODEV ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_send_wakeup_ipi_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_bootaddr ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
r9a06g032_smp_boot_secondary(unsigned int cpu,
			     struct task_struct *idle)
{
	if (!cpu_bootaddr)
		return -ENODEV;

	spin_lock(&cpu_lock);

	writel(__pa_symbol(secondary_startup), cpu_bootaddr);
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	spin_unlock(&cpu_lock);

	return 0;
}