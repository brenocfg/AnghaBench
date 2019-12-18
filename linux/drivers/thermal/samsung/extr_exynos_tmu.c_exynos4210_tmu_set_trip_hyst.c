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
typedef  int /*<<< orphan*/  u8 ;
struct exynos_tmu_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void exynos4210_tmu_set_trip_hyst(struct exynos_tmu_data *data,
					 int trip, u8 temp, u8 hyst)
{
}