#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct mt9v032 {int /*<<< orphan*/  ctrls; TYPE_2__* model; TYPE_3__* pdata; struct regmap* regmap; } ;
struct TYPE_6__ {scalar_t__ clk_pol; } ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  pclk_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9V032_PIXEL_CLOCK_INV_PXL_CLK ; 
 int /*<<< orphan*/  MT9V032_ROW_NOISE_CORR_CONTROL ; 
 int /*<<< orphan*/  mt9v032_power_off (struct mt9v032*) ; 
 int mt9v032_power_on (struct mt9v032*) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __mt9v032_set_power(struct mt9v032 *mt9v032, bool on)
{
	struct regmap *map = mt9v032->regmap;
	int ret;

	if (!on) {
		mt9v032_power_off(mt9v032);
		return 0;
	}

	ret = mt9v032_power_on(mt9v032);
	if (ret < 0)
		return ret;

	/* Configure the pixel clock polarity */
	if (mt9v032->pdata && mt9v032->pdata->clk_pol) {
		ret = regmap_write(map, mt9v032->model->data->pclk_reg,
				MT9V032_PIXEL_CLOCK_INV_PXL_CLK);
		if (ret < 0)
			return ret;
	}

	/* Disable the noise correction algorithm and restore the controls. */
	ret = regmap_write(map, MT9V032_ROW_NOISE_CORR_CONTROL, 0);
	if (ret < 0)
		return ret;

	return v4l2_ctrl_handler_setup(&mt9v032->ctrls);
}