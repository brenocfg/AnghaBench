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
struct exynos_tmu_data {scalar_t__ base; } ;

/* Variables and functions */
 int EXYNOS7_TMU_TEMP_MASK ; 
 scalar_t__ EXYNOS_TMU_REG_CURRENT_TEMP ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int exynos7_tmu_read(struct exynos_tmu_data *data)
{
	return readw(data->base + EXYNOS_TMU_REG_CURRENT_TEMP) &
		EXYNOS7_TMU_TEMP_MASK;
}