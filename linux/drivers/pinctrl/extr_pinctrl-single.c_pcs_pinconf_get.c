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
struct pcs_function {unsigned int nconfs; TYPE_1__* conf; } ;
struct pcs_device {unsigned int width; unsigned int (* read ) (scalar_t__) ;scalar_t__ base; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
struct TYPE_2__ {int param; unsigned int mask; unsigned int enable; unsigned int disable; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int ENOTSUPP ; 
 int PIN_CONFIG_BIAS_DISABLE ; 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_INPUT_SCHMITT 131 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 130 
#define  PIN_CONFIG_LOW_POWER_MODE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 unsigned int pcs_get_function (struct pinctrl_dev*,unsigned int,struct pcs_function**) ; 
 scalar_t__ pcs_pinconf_bias_disable (struct pinctrl_dev*,unsigned int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct pcs_device* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 unsigned int stub1 (scalar_t__) ; 

__attribute__((used)) static int pcs_pinconf_get(struct pinctrl_dev *pctldev,
				unsigned pin, unsigned long *config)
{
	struct pcs_device *pcs = pinctrl_dev_get_drvdata(pctldev);
	struct pcs_function *func;
	enum pin_config_param param;
	unsigned offset = 0, data = 0, i, j, ret;

	ret = pcs_get_function(pctldev, pin, &func);
	if (ret)
		return ret;

	for (i = 0; i < func->nconfs; i++) {
		param = pinconf_to_config_param(*config);
		if (param == PIN_CONFIG_BIAS_DISABLE) {
			if (pcs_pinconf_bias_disable(pctldev, pin)) {
				*config = 0;
				return 0;
			} else {
				return -ENOTSUPP;
			}
		} else if (param != func->conf[i].param) {
			continue;
		}

		offset = pin * (pcs->width / BITS_PER_BYTE);
		data = pcs->read(pcs->base + offset) & func->conf[i].mask;
		switch (func->conf[i].param) {
		/* 4 parameters */
		case PIN_CONFIG_BIAS_PULL_DOWN:
		case PIN_CONFIG_BIAS_PULL_UP:
		case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			if ((data != func->conf[i].enable) ||
			    (data == func->conf[i].disable))
				return -ENOTSUPP;
			*config = 0;
			break;
		/* 2 parameters */
		case PIN_CONFIG_INPUT_SCHMITT:
			for (j = 0; j < func->nconfs; j++) {
				switch (func->conf[j].param) {
				case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
					if (data != func->conf[j].enable)
						return -ENOTSUPP;
					break;
				default:
					break;
				}
			}
			*config = data;
			break;
		case PIN_CONFIG_DRIVE_STRENGTH:
		case PIN_CONFIG_SLEW_RATE:
		case PIN_CONFIG_LOW_POWER_MODE:
		default:
			*config = data;
			break;
		}
		return 0;
	}
	return -ENOTSUPP;
}