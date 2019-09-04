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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS5_ARM_CORE0_SYS_PWR_REG ; 
 int /*<<< orphan*/  EXYNOS_ARM_CORE_CONFIGURATION (int) ; 
 int S5P_CORE_LOCAL_PWR_EN ; 
 int pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ soc_is_exynos5420 () ; 
 scalar_t__ soc_is_exynos5800 () ; 

void exynos_cpu_power_down(int cpu)
{
	u32 core_conf;

	if (cpu == 0 && (soc_is_exynos5420() || soc_is_exynos5800())) {
		/*
		 * Bypass power down for CPU0 during suspend. Check for
		 * the SYS_PWR_REG value to decide if we are suspending
		 * the system.
		 */
		int val = pmu_raw_readl(EXYNOS5_ARM_CORE0_SYS_PWR_REG);

		if (!(val & S5P_CORE_LOCAL_PWR_EN))
			return;
	}

	core_conf = pmu_raw_readl(EXYNOS_ARM_CORE_CONFIGURATION(cpu));
	core_conf &= ~S5P_CORE_LOCAL_PWR_EN;
	pmu_raw_writel(core_conf, EXYNOS_ARM_CORE_CONFIGURATION(cpu));
}