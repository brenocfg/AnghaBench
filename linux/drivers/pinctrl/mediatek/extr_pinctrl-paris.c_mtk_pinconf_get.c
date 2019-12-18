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
typedef  int u32 ;
struct pinctrl_dev {int dummy; } ;
struct mtk_pinctrl {TYPE_1__* soc; } ;
struct mtk_pin_desc {int dummy; } ;
struct TYPE_2__ {int (* bias_disable_get ) (struct mtk_pinctrl*,struct mtk_pin_desc const*,int*) ;int (* bias_get ) (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,int*) ;int (* drive_get ) (struct mtk_pinctrl*,struct mtk_pin_desc const*,int*) ;int (* adv_pull_get ) (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,int*) ;int (* adv_drive_get ) (struct mtk_pinctrl*,struct mtk_pin_desc const*,int*) ;int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  MTK_PIN_CONFIG_DRV_ADV 140 
#define  MTK_PIN_CONFIG_PD_ADV 139 
#define  MTK_PIN_CONFIG_PU_ADV 138 
#define  MTK_PIN_CONFIG_RDSEL 137 
#define  MTK_PIN_CONFIG_TDSEL 136 
 int PINCTRL_PIN_REG_DIR ; 
 int PINCTRL_PIN_REG_RDSEL ; 
 int PINCTRL_PIN_REG_SMT ; 
 int PINCTRL_PIN_REG_SR ; 
 int PINCTRL_PIN_REG_TDSEL ; 
#define  PIN_CONFIG_BIAS_DISABLE 135 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_INPUT_ENABLE 131 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 130 
#define  PIN_CONFIG_OUTPUT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int mtk_hw_get_value (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,int*) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct mtk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int stub1 (struct mtk_pinctrl*,struct mtk_pin_desc const*,int*) ; 
 int stub2 (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,int*) ; 
 int stub3 (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,int*) ; 
 int stub4 (struct mtk_pinctrl*,struct mtk_pin_desc const*,int*) ; 
 int stub5 (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,int*) ; 
 int stub6 (struct mtk_pinctrl*,struct mtk_pin_desc const*,int*) ; 

__attribute__((used)) static int mtk_pinconf_get(struct pinctrl_dev *pctldev,
			   unsigned int pin, unsigned long *config)
{
	struct mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	int val, val2, err, reg, ret = 1;
	const struct mtk_pin_desc *desc;

	desc = (const struct mtk_pin_desc *)&hw->soc->pins[pin];

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (hw->soc->bias_disable_get) {
			err = hw->soc->bias_disable_get(hw, desc, &ret);
			if (err)
				return err;
		} else {
			return -ENOTSUPP;
		}
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		if (hw->soc->bias_get) {
			err = hw->soc->bias_get(hw, desc, 1, &ret);
			if (err)
				return err;
		} else {
			return -ENOTSUPP;
		}
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (hw->soc->bias_get) {
			err = hw->soc->bias_get(hw, desc, 0, &ret);
			if (err)
				return err;
		} else {
			return -ENOTSUPP;
		}
		break;
	case PIN_CONFIG_SLEW_RATE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_SR, &val);
		if (err)
			return err;

		if (!val)
			return -EINVAL;

		break;
	case PIN_CONFIG_INPUT_ENABLE:
	case PIN_CONFIG_OUTPUT_ENABLE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DIR, &val);
		if (err)
			return err;

		/* HW takes input mode as zero; output mode as non-zero */
		if ((val && param == PIN_CONFIG_INPUT_ENABLE) ||
		    (!val && param == PIN_CONFIG_OUTPUT_ENABLE))
			return -EINVAL;

		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DIR, &val);
		if (err)
			return err;

		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_SMT, &val2);
		if (err)
			return err;

		if (val || !val2)
			return -EINVAL;

		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		if (hw->soc->drive_get) {
			err = hw->soc->drive_get(hw, desc, &ret);
			if (err)
				return err;
		} else {
			err = -ENOTSUPP;
		}
		break;
	case MTK_PIN_CONFIG_TDSEL:
	case MTK_PIN_CONFIG_RDSEL:
		reg = (param == MTK_PIN_CONFIG_TDSEL) ?
		       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;

		err = mtk_hw_get_value(hw, desc, reg, &val);
		if (err)
			return err;

		ret = val;

		break;
	case MTK_PIN_CONFIG_PU_ADV:
	case MTK_PIN_CONFIG_PD_ADV:
		if (hw->soc->adv_pull_get) {
			bool pullup;

			pullup = param == MTK_PIN_CONFIG_PU_ADV;
			err = hw->soc->adv_pull_get(hw, desc, pullup, &ret);
			if (err)
				return err;
		} else {
			return -ENOTSUPP;
		}
		break;
	case MTK_PIN_CONFIG_DRV_ADV:
		if (hw->soc->adv_drive_get) {
			err = hw->soc->adv_drive_get(hw, desc, &ret);
			if (err)
				return err;
		} else {
			return -ENOTSUPP;
		}
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, ret);

	return 0;
}