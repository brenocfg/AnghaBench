#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_2__* desc; } ;
struct TYPE_6__ {int base; } ;
struct ns2_pin {TYPE_3__ pin_conf; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_5__ {TYPE_1__* pins; } ;
struct TYPE_4__ {struct ns2_pin* drv_data; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 133 
#define  PIN_CONFIG_BIAS_PULL_DOWN 132 
#define  PIN_CONFIG_BIAS_PULL_UP 131 
#define  PIN_CONFIG_DRIVE_STRENGTH 130 
#define  PIN_CONFIG_INPUT_ENABLE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ns2_pin_set_enable (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int ns2_pin_set_pull (struct pinctrl_dev*,unsigned int,int,int) ; 
 int ns2_pin_set_slew (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int ns2_pin_set_strength (struct pinctrl_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int ns2_pin_config_set(struct pinctrl_dev *pctrldev, unsigned int pin,
			      unsigned long *configs, unsigned int num_configs)
{
	struct ns2_pin *pin_data = pctrldev->desc->pins[pin].drv_data;
	enum pin_config_param param;
	unsigned int i;
	u32 arg;
	int ret = -ENOTSUPP;

	if (pin_data->pin_conf.base == -1)
		return -ENOTSUPP;

	for (i = 0; i < num_configs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
			ret = ns2_pin_set_pull(pctrldev, pin, false, false);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_BIAS_PULL_UP:
			ret = ns2_pin_set_pull(pctrldev, pin, true, false);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_BIAS_PULL_DOWN:
			ret = ns2_pin_set_pull(pctrldev, pin, false, true);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_DRIVE_STRENGTH:
			ret = ns2_pin_set_strength(pctrldev, pin, arg);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_SLEW_RATE:
			ret = ns2_pin_set_slew(pctrldev, pin, arg);
			if (ret < 0)
				goto out;
			break;

		case PIN_CONFIG_INPUT_ENABLE:
			ret = ns2_pin_set_enable(pctrldev, pin, arg);
			if (ret < 0)
				goto out;
			break;

		default:
			dev_err(pctrldev->dev, "invalid configuration\n");
			return -ENOTSUPP;
		}
	}
out:
	return ret;
}