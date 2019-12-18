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
typedef  unsigned int u32 ;
struct rk805_pctrl_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  gpio_chip; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_OUTPUT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct rk805_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  rk805_gpio_set (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rk805_pmx_gpio_set_direction (struct pinctrl_dev*,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int rk805_pinconf_set(struct pinctrl_dev *pctldev,
			     unsigned int pin, unsigned long *configs,
			     unsigned int num_configs)
{
	struct rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param;
	u32 i, arg = 0;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_OUTPUT:
			rk805_gpio_set(&pci->gpio_chip, pin, arg);
			rk805_pmx_gpio_set_direction(pctldev, NULL, pin, false);
			break;
		default:
			dev_err(pci->dev, "Properties not supported\n");
			return -ENOTSUPP;
		}
	}

	return 0;
}