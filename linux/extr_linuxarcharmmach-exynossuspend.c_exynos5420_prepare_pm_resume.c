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
 int /*<<< orphan*/  CONFIG_EXYNOS5420_MCPM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpm_cpu_powered_up () ; 

__attribute__((used)) static void exynos5420_prepare_pm_resume(void)
{
	if (IS_ENABLED(CONFIG_EXYNOS5420_MCPM))
		WARN_ON(mcpm_cpu_powered_up());
}