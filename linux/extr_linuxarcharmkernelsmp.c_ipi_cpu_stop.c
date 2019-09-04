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
 scalar_t__ SYSTEM_RUNNING ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  pr_crit (char*,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 
 int /*<<< orphan*/  stop_lock ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  wfe () ; 

__attribute__((used)) static void ipi_cpu_stop(unsigned int cpu)
{
	if (system_state <= SYSTEM_RUNNING) {
		raw_spin_lock(&stop_lock);
		pr_crit("CPU%u: stopping\n", cpu);
		dump_stack();
		raw_spin_unlock(&stop_lock);
	}

	set_cpu_online(cpu, false);

	local_fiq_disable();
	local_irq_disable();

	while (1) {
		cpu_relax();
		wfe();
	}
}