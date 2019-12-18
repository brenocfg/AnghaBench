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
struct sc27xx_fgu_data {int init_clbcnt; int total_cap; int init_cap; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int SC27XX_FGU_SAMPLE_HZ ; 
 int sc27xx_fgu_adc_to_current (struct sc27xx_fgu_data*,int) ; 
 int /*<<< orphan*/  sc27xx_fgu_capacity_calibration (struct sc27xx_fgu_data*,int,int) ; 
 int sc27xx_fgu_get_clbcnt (struct sc27xx_fgu_data*,int*) ; 

__attribute__((used)) static int sc27xx_fgu_get_capacity(struct sc27xx_fgu_data *data, int *cap)
{
	int ret, cur_clbcnt, delta_clbcnt, delta_cap, temp;

	/* Get current coulomb counters firstly */
	ret = sc27xx_fgu_get_clbcnt(data, &cur_clbcnt);
	if (ret)
		return ret;

	delta_clbcnt = cur_clbcnt - data->init_clbcnt;

	/*
	 * Convert coulomb counter to delta capacity (mAh), and set multiplier
	 * as 10 to improve the precision.
	 */
	temp = DIV_ROUND_CLOSEST(delta_clbcnt * 10, 36 * SC27XX_FGU_SAMPLE_HZ);
	temp = sc27xx_fgu_adc_to_current(data, temp / 1000);

	/*
	 * Convert to capacity percent of the battery total capacity,
	 * and multiplier is 100 too.
	 */
	delta_cap = DIV_ROUND_CLOSEST(temp * 100, data->total_cap);
	*cap = delta_cap + data->init_cap;

	/* Calibrate the battery capacity in a normal range. */
	sc27xx_fgu_capacity_calibration(data, *cap, false);

	return 0;
}