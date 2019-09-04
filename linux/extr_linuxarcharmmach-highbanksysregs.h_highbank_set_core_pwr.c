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
 int MPIDR_AFFINITY_LEVEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_PM_POWEROFF ; 
 scalar_t__ SREG_CPU_PWR_CTRL (int) ; 
 int /*<<< orphan*/  cpu_logical_map (int /*<<< orphan*/ ) ; 
 scalar_t__ scu_base_addr ; 
 int /*<<< orphan*/  scu_power_mode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ sregs_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void highbank_set_core_pwr(void)
{
	int cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(smp_processor_id()), 0);
	if (scu_base_addr)
		scu_power_mode(scu_base_addr, SCU_PM_POWEROFF);
	else
		writel_relaxed(1, sregs_base + SREG_CPU_PWR_CTRL(cpu));
}