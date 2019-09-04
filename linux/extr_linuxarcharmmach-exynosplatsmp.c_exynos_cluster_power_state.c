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
 int /*<<< orphan*/  EXYNOS_COMMON_STATUS (int) ; 
 int S5P_CORE_LOCAL_PWR_EN ; 
 int pmu_raw_readl (int /*<<< orphan*/ ) ; 

int exynos_cluster_power_state(int cluster)
{
	return (pmu_raw_readl(EXYNOS_COMMON_STATUS(cluster)) &
		S5P_CORE_LOCAL_PWR_EN);
}