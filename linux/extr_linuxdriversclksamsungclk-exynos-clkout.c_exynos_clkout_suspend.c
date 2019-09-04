#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ reg; int /*<<< orphan*/  pmu_debug_save; } ;

/* Variables and functions */
 scalar_t__ EXYNOS_PMU_DEBUG_REG ; 
 TYPE_1__* clkout ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int exynos_clkout_suspend(void)
{
	clkout->pmu_debug_save = readl(clkout->reg + EXYNOS_PMU_DEBUG_REG);

	return 0;
}