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
 int /*<<< orphan*/  S5P_INFORM0 ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_cpu_resume ; 
 int /*<<< orphan*/  exynos_pm_enter_sleep_mode () ; 
 int /*<<< orphan*/  exynos_pm_set_wakeup_mask () ; 
 int /*<<< orphan*/  exynos_set_delayed_reset_assertion (int) ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_pm_prepare(void)
{
	exynos_set_delayed_reset_assertion(false);

	/* Set wake-up mask registers */
	exynos_pm_set_wakeup_mask();

	exynos_pm_enter_sleep_mode();

	/* ensure at least INFORM0 has the resume address */
	pmu_raw_writel(__pa_symbol(exynos_cpu_resume), S5P_INFORM0);
}