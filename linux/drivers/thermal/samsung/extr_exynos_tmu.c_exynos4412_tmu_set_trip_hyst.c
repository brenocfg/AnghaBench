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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct exynos_tmu_data {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EXYNOS_THD_TEMP_FALL ; 
 int readl (scalar_t__) ; 
 int temp_to_code (struct exynos_tmu_data*,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos4412_tmu_set_trip_hyst(struct exynos_tmu_data *data,
					 int trip, u8 temp, u8 hyst)
{
	u32 th;

	th = readl(data->base + EXYNOS_THD_TEMP_FALL);
	th &= ~(0xff << 8 * trip);
	if (hyst)
		th |= temp_to_code(data, temp - hyst) << 8 * trip;
	writel(th, data->base + EXYNOS_THD_TEMP_FALL);
}