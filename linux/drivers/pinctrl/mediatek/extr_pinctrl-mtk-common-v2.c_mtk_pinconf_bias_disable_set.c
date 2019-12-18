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
struct mtk_pin_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_DISABLE ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_PD ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_PU ; 
 int mtk_hw_set_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mtk_pinconf_bias_disable_set(struct mtk_pinctrl *hw,
				 const struct mtk_pin_desc *desc)
{
	int err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU,
			       MTK_DISABLE);
	if (err)
		return err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD,
			       MTK_DISABLE);
	if (err)
		return err;

	return 0;
}