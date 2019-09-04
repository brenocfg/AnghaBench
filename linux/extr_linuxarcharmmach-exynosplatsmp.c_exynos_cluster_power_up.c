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
 int /*<<< orphan*/  EXYNOS_COMMON_CONFIGURATION (int) ; 
 int /*<<< orphan*/  S5P_CORE_LOCAL_PWR_EN ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void exynos_cluster_power_up(int cluster)
{
	pmu_raw_writel(S5P_CORE_LOCAL_PWR_EN,
			EXYNOS_COMMON_CONFIGURATION(cluster));
}