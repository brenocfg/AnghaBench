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
struct oxnas_pinctrl {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {scalar_t__ base; } ;
struct oxnas_gpio_bank {TYPE_1__ gpio_chip; scalar_t__ id; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int ENOTSUPP ; 
 unsigned int PINMUX_820_BANK_OFFSET ; 
 int /*<<< orphan*/  PINMUX_820_PULLUP_CTRL ; 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 struct oxnas_gpio_bank* pctl_to_bank (struct oxnas_pinctrl*,unsigned int) ; 
 unsigned long pinconf_to_config_packed (unsigned int,int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct oxnas_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int oxnas_ox820_pinconf_get(struct pinctrl_dev *pctldev,
				   unsigned int pin, unsigned long *config)
{
	struct oxnas_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct oxnas_gpio_bank *bank = pctl_to_bank(pctl, pin);
	unsigned int param = pinconf_to_config_param(*config);
	unsigned int bank_offset = (bank->id ? PINMUX_820_BANK_OFFSET : 0);
	u32 mask = BIT(pin - bank->gpio_chip.base);
	int ret;
	u32 arg;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
		ret = regmap_read(pctl->regmap,
				  bank_offset + PINMUX_820_PULLUP_CTRL,
				  &arg);
		if (ret)
			return ret;

		arg = !!(arg & mask);
		break;
	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}