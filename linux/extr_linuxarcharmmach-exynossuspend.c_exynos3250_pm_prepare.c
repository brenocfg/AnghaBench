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
 int /*<<< orphan*/  EXYNOS3_ARM_L2_OPTION ; 
 unsigned int EXYNOS5_OPTION_USE_RETENTION ; 
 int /*<<< orphan*/  S5P_INFORM0 ; 
 unsigned int __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_cpu_resume ; 
 int /*<<< orphan*/  exynos_pm_enter_sleep_mode () ; 
 int /*<<< orphan*/  exynos_pm_set_wakeup_mask () ; 
 unsigned int pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos3250_pm_prepare(void)
{
	unsigned int tmp;

	/* Set wake-up mask registers */
	exynos_pm_set_wakeup_mask();

	tmp = pmu_raw_readl(EXYNOS3_ARM_L2_OPTION);
	tmp &= ~EXYNOS5_OPTION_USE_RETENTION;
	pmu_raw_writel(tmp, EXYNOS3_ARM_L2_OPTION);

	exynos_pm_enter_sleep_mode();

	/* ensure at least INFORM0 has the resume address */
	pmu_raw_writel(__pa_symbol(exynos_cpu_resume), S5P_INFORM0);
}