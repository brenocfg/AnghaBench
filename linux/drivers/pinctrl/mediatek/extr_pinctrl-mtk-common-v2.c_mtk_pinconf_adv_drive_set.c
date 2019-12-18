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
struct mtk_pinctrl {int dummy; } ;
struct mtk_pin_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINCTRL_PIN_REG_DRV_E0 ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_DRV_E1 ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_DRV_EN ; 
 int mtk_hw_set_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int /*<<< orphan*/ ,int) ; 

int mtk_pinconf_adv_drive_set(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, u32 arg)
{
	int err;
	int en = arg & 1;
	int e0 = !!(arg & 2);
	int e1 = !!(arg & 4);

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_EN, en);
	if (err)
		return err;

	if (!en)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_E0, e0);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_E1, e1);
	if (err)
		return err;

	return err;
}