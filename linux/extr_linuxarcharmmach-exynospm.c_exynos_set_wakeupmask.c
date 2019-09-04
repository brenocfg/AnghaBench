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
 int /*<<< orphan*/  S5P_WAKEUP_MASK ; 
 int /*<<< orphan*/  S5P_WAKEUP_MASK2 ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ soc_is_exynos3250 () ; 

__attribute__((used)) static void exynos_set_wakeupmask(long mask)
{
	pmu_raw_writel(mask, S5P_WAKEUP_MASK);
	if (soc_is_exynos3250())
		pmu_raw_writel(0x0, S5P_WAKEUP_MASK2);
}