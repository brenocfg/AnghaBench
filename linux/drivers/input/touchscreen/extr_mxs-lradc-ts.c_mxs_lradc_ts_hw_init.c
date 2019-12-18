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
struct mxs_lradc_ts {scalar_t__ base; struct mxs_lradc* lradc; } ;
struct mxs_lradc {scalar_t__ soc; scalar_t__ touchscreen_wire; } ;

/* Variables and functions */
 scalar_t__ IMX28_LRADC ; 
 scalar_t__ LRADC_CTRL0 ; 
 int /*<<< orphan*/  LRADC_CTRL0_MX28_TOUCH_SCREEN_TYPE ; 
 scalar_t__ MXS_LRADC_TOUCHSCREEN_5WIRE ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_ts_hw_init(struct mxs_lradc_ts *ts)
{
	struct mxs_lradc *lradc = ts->lradc;

	/* Configure the touchscreen type */
	if (lradc->soc == IMX28_LRADC) {
		writel(LRADC_CTRL0_MX28_TOUCH_SCREEN_TYPE,
		       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);

		if (lradc->touchscreen_wire == MXS_LRADC_TOUCHSCREEN_5WIRE)
			writel(LRADC_CTRL0_MX28_TOUCH_SCREEN_TYPE,
			       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);
	}
}