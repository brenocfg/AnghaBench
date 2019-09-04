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
 int /*<<< orphan*/  EXYNOS_EINT_WAKEUP_MASK ; 
 int /*<<< orphan*/  S5P_WAKEUP_MASK ; 
 int exynos_get_eint_wake_mask () ; 
 int exynos_irqwake_intmask ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_pm_set_wakeup_mask(void)
{
	/* Set wake-up mask registers */
	pmu_raw_writel(exynos_get_eint_wake_mask(), EXYNOS_EINT_WAKEUP_MASK);
	pmu_raw_writel(exynos_irqwake_intmask & ~(1 << 31), S5P_WAKEUP_MASK);
}