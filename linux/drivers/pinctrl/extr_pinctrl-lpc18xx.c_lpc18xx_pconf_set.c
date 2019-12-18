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
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_dev {int dummy; } ;
struct lpc18xx_scu_data {scalar_t__ base; } ;
struct lpc18xx_pin_caps {scalar_t__ type; scalar_t__ offset; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TYPE_I2C0 ; 
 scalar_t__ TYPE_USB1 ; 
 struct lpc18xx_pin_caps* lpc18xx_get_pin_caps (unsigned int) ; 
 int lpc18xx_pconf_set_i2c0 (struct pinctrl_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int lpc18xx_pconf_set_pin (struct pinctrl_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,struct lpc18xx_pin_caps*) ; 
 int lpc18xx_pconf_set_usb1 (struct pinctrl_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct lpc18xx_scu_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_pconf_set(struct pinctrl_dev *pctldev, unsigned pin,
			     unsigned long *configs, unsigned num_configs)
{
	struct lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	struct lpc18xx_pin_caps *pin_cap;
	enum pin_config_param param;
	u32 param_val;
	u32 reg;
	int ret;
	int i;

	pin_cap = lpc18xx_get_pin_caps(pin);
	if (!pin_cap)
		return -EINVAL;

	reg = readl(scu->base + pin_cap->offset);

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);

		if (pin_cap->type == TYPE_I2C0)
			ret = lpc18xx_pconf_set_i2c0(pctldev, param, param_val, &reg, pin);
		else if (pin_cap->type == TYPE_USB1)
			ret = lpc18xx_pconf_set_usb1(pctldev, param, param_val, &reg);
		else
			ret = lpc18xx_pconf_set_pin(pctldev, param, param_val, &reg, pin, pin_cap);

		if (ret)
			return ret;
	}

	writel(reg, scu->base + pin_cap->offset);

	return 0;
}