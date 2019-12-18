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
 int mtk_hw_get_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int /*<<< orphan*/ ,int*) ; 

int mtk_pinconf_adv_drive_get(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, u32 *val)
{
	u32 en, e0, e1;
	int err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_EN, &en);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_E0, &e0);
	if (err)
		return err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_E1, &e1);
	if (err)
		return err;

	*val = (en | e0 << 1 | e1 << 2) & 0x7;

	return 0;
}