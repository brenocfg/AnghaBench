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
typedef  int u32 ;
struct lm3530_platform_data {scalar_t__ als_vmax; int als_vmin; int als_avrg_time; int als_input_mode; int als1_resistor_sel; int als2_resistor_sel; } ;
struct lm3530_als_data {int* zones; int config; int imp_sel; } ;

/* Variables and functions */
 int LED_FULL ; 
 int LM3530_ALS1_IMP_SHIFT ; 
 int LM3530_ALS2_IMP_SHIFT ; 
 int LM3530_ALS_AVG_TIME_SHIFT ; 
 int LM3530_ALS_OFFSET_mV ; 
 int LM3530_ALS_SEL_SHIFT ; 
 int LM3530_ALS_WINDOW_mV ; 
 int LM3530_ALS_ZB_MAX ; 
 int LM3530_ENABLE_ALS ; 

__attribute__((used)) static void lm3530_als_configure(struct lm3530_platform_data *pdata,
				struct lm3530_als_data *als)
{
	int i;
	u32 als_vmin, als_vmax, als_vstep;

	if (pdata->als_vmax == 0) {
		pdata->als_vmin = 0;
		pdata->als_vmax = LM3530_ALS_WINDOW_mV;
	}

	als_vmin = pdata->als_vmin;
	als_vmax = pdata->als_vmax;

	if ((als_vmax - als_vmin) > LM3530_ALS_WINDOW_mV)
		pdata->als_vmax = als_vmax = als_vmin + LM3530_ALS_WINDOW_mV;

	/* n zone boundary makes n+1 zones */
	als_vstep = (als_vmax - als_vmin) / (LM3530_ALS_ZB_MAX + 1);

	for (i = 0; i < LM3530_ALS_ZB_MAX; i++)
		als->zones[i] = (((als_vmin + LM3530_ALS_OFFSET_mV) +
			als_vstep + (i * als_vstep)) * LED_FULL) / 1000;

	als->config =
		(pdata->als_avrg_time << LM3530_ALS_AVG_TIME_SHIFT) |
		(LM3530_ENABLE_ALS) |
		(pdata->als_input_mode << LM3530_ALS_SEL_SHIFT);

	als->imp_sel =
		(pdata->als1_resistor_sel << LM3530_ALS1_IMP_SHIFT) |
		(pdata->als2_resistor_sel << LM3530_ALS2_IMP_SHIFT);
}