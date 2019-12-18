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
struct sc27xx_fgu_data {int total_cap; int cur_1000ma_adc; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int SC27XX_FGU_SAMPLE_HZ ; 

__attribute__((used)) static int sc27xx_fgu_cap_to_clbcnt(struct sc27xx_fgu_data *data, int capacity)
{
	/*
	 * Get current capacity (mAh) = battery total capacity (mAh) *
	 * current capacity percent (capacity / 100).
	 */
	int cur_cap = DIV_ROUND_CLOSEST(data->total_cap * capacity, 100);

	/*
	 * Convert current capacity (mAh) to coulomb counter according to the
	 * formula: 1 mAh =3.6 coulomb.
	 */
	return DIV_ROUND_CLOSEST(cur_cap * 36 * data->cur_1000ma_adc * SC27XX_FGU_SAMPLE_HZ, 10);
}