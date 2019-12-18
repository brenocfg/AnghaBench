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
 int EINVAL ; 
 int MTK_DISABLE ; 
 int MTK_PULLUP ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_PULLEN ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_PULLSEL ; 
 int mtk_hw_get_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int /*<<< orphan*/ ,int*) ; 

int mtk_pinconf_bias_get_rev1(struct mtk_pinctrl *hw,
			      const struct mtk_pin_desc *desc, bool pullup,
			      int *res)
{
	int err, v;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, &v);
	if (err)
		return err;

	if (v == MTK_DISABLE)
		return -EINVAL;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, &v);
	if (err)
		return err;

	if (pullup ^ (v == MTK_PULLUP))
		return -EINVAL;

	*res = 1;

	return 0;
}