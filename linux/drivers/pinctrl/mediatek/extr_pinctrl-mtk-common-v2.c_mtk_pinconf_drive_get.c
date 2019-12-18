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
struct mtk_pinctrl {int dummy; } ;
struct mtk_pin_desc {size_t drv_n; } ;
struct mtk_drive_desc {int scal; int step; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINCTRL_PIN_REG_E4 ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_E8 ; 
 struct mtk_drive_desc* mtk_drive ; 
 int mtk_hw_get_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int /*<<< orphan*/ ,int*) ; 

int mtk_pinconf_drive_get(struct mtk_pinctrl *hw,
			  const struct mtk_pin_desc *desc, int *val)
{
	const struct mtk_drive_desc *tb;
	int err, val1, val2;

	tb = &mtk_drive[desc->drv_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_E4, &val1);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_E8, &val2);
	if (err)
		return err;

	/* 4mA when (e8, e4) = (0, 0); 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0); 16mA when (e8, e4) = (1, 1)
	 */
	*val = (((val2 << 1) + val1) / tb->scal + 1) * tb->step;

	return 0;
}