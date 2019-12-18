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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rk805_pctrl_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  gpio_chip; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long pinconf_to_config_packed (int,int /*<<< orphan*/ ) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct rk805_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 scalar_t__ rk805_gpio_get (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int rk805_pinconf_get(struct pinctrl_dev *pctldev,
			     unsigned int pin, unsigned long *config)
{
	struct rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	u32 arg = 0;

	switch (param) {
	case PIN_CONFIG_OUTPUT:
		arg = rk805_gpio_get(&pci->gpio_chip, pin);
		break;
	default:
		dev_err(pci->dev, "Properties not supported\n");
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, (u16)arg);

	return 0;
}