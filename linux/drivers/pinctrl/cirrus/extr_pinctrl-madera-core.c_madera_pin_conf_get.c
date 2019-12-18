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
struct madera_pin_private {int /*<<< orphan*/  dev; TYPE_1__* madera; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 unsigned int MADERA_GP1_DB_MASK ; 
 unsigned int MADERA_GP1_DIR_MASK ; 
 unsigned int MADERA_GP1_IP_CFG_MASK ; 
 unsigned int MADERA_GP1_LVL_MASK ; 
 unsigned int MADERA_GP1_OP_CFG_MASK ; 
 unsigned int MADERA_GP1_PD ; 
 unsigned int MADERA_GP1_PD_MASK ; 
 unsigned int MADERA_GP1_PU ; 
 unsigned int MADERA_GP1_PU_MASK ; 
 int MADERA_GPIO1_CTRL_1 ; 
#define  PIN_CONFIG_BIAS_BUS_HOLD 139 
#define  PIN_CONFIG_BIAS_DISABLE 138 
#define  PIN_CONFIG_BIAS_PULL_DOWN 137 
#define  PIN_CONFIG_BIAS_PULL_UP 136 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 135 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 134 
#define  PIN_CONFIG_DRIVE_STRENGTH 133 
#define  PIN_CONFIG_INPUT_DEBOUNCE 132 
#define  PIN_CONFIG_INPUT_ENABLE 131 
#define  PIN_CONFIG_INPUT_SCHMITT 130 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 129 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 unsigned int madera_pin_unmake_drv_str (struct madera_pin_private*,unsigned int) ; 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct madera_pin_private* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int madera_pin_conf_get(struct pinctrl_dev *pctldev, unsigned int pin,
			       unsigned long *config)
{
	struct madera_pin_private *priv = pinctrl_dev_get_drvdata(pctldev);
	unsigned int param = pinconf_to_config_param(*config);
	unsigned int result = 0;
	unsigned int reg = MADERA_GPIO1_CTRL_1 + (2 * pin);
	unsigned int conf[2];
	int ret;

	ret = regmap_read(priv->madera->regmap, reg, &conf[0]);
	if (!ret)
		ret = regmap_read(priv->madera->regmap, reg + 1, &conf[1]);

	if (ret) {
		dev_err(priv->dev, "Failed to read GP%d conf (%d)\n",
			pin + 1, ret);
		return ret;
	}

	switch (param) {
	case PIN_CONFIG_BIAS_BUS_HOLD:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		if (conf[1] == (MADERA_GP1_PU | MADERA_GP1_PD))
			result = 1;
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		if (!conf[1])
			result = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		if (conf[1] == MADERA_GP1_PD_MASK)
			result = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		conf[1] &= MADERA_GP1_PU_MASK | MADERA_GP1_PD_MASK;
		if (conf[1] == MADERA_GP1_PU_MASK)
			result = 1;
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (conf[0] & MADERA_GP1_OP_CFG_MASK)
			result = 1;
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		if (!(conf[0] & MADERA_GP1_OP_CFG_MASK))
			result = 1;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		result = madera_pin_unmake_drv_str(priv, conf[1]);
		break;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		if (conf[0] & MADERA_GP1_DB_MASK)
			result = 1;
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		if (conf[0] & MADERA_GP1_DIR_MASK)
			result = 1;
		break;
	case PIN_CONFIG_INPUT_SCHMITT:
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (conf[0] & MADERA_GP1_IP_CFG_MASK)
			result = 1;
		break;
	case PIN_CONFIG_OUTPUT:
		if ((conf[1] & MADERA_GP1_DIR_MASK) &&
		    (conf[0] & MADERA_GP1_LVL_MASK))
			result = 1;
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, result);

	return 0;
}