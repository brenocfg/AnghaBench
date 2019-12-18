#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl_group {size_t pin; } ;
struct mtk_pinctrl {TYPE_1__* soc; int /*<<< orphan*/  dev; struct mtk_pinctrl_group* groups; } ;
struct mtk_pin_desc {int dummy; } ;
struct mtk_func_desc {int /*<<< orphan*/  muxval; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PINCTRL_PIN_REG_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mtk_hw_set_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_func_desc* mtk_pctrl_find_function_by_pin (struct mtk_pinctrl*,size_t,unsigned int) ; 
 int mtk_pctrl_is_function_valid (struct mtk_pinctrl*,size_t,unsigned int) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mtk_pmx_set_mux(struct pinctrl_dev *pctldev,
			   unsigned function,
			   unsigned group)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	struct mtk_pinctrl_group *grp = hw->groups + group;
	const struct mtk_func_desc *desc_func;
	const struct mtk_pin_desc *desc;
	bool ret;

	ret = mtk_pctrl_is_function_valid(hw, grp->pin, function);
	if (!ret) {
		dev_err(hw->dev, "invalid function %d on group %d .\n",
			function, group);
		return -EINVAL;
	}

	desc_func = mtk_pctrl_find_function_by_pin(hw, grp->pin, function);
	if (!desc_func)
		return -EINVAL;

	desc = (const struct mtk_pin_desc *)&hw->soc->pins[grp->pin];
	mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_MODE, desc_func->muxval);

	return 0;
}