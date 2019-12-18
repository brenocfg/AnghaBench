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
struct chv_pinctrl {int /*<<< orphan*/  dev; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 int chv_config_set_oden (struct chv_pinctrl*,unsigned int,int) ; 
 int chv_config_set_pull (struct chv_pinctrl*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ chv_pad_locked (struct chv_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct chv_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int chv_config_set(struct pinctrl_dev *pctldev, unsigned int pin,
			  unsigned long *configs, unsigned int nconfigs)
{
	struct chv_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param;
	int i, ret;
	u32 arg;

	if (chv_pad_locked(pctrl, pin))
		return -EBUSY;

	for (i = 0; i < nconfigs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_BIAS_DISABLE:
		case PIN_CONFIG_BIAS_PULL_UP:
		case PIN_CONFIG_BIAS_PULL_DOWN:
			ret = chv_config_set_pull(pctrl, pin, param, arg);
			if (ret)
				return ret;
			break;

		case PIN_CONFIG_DRIVE_PUSH_PULL:
			ret = chv_config_set_oden(pctrl, pin, false);
			if (ret)
				return ret;
			break;

		case PIN_CONFIG_DRIVE_OPEN_DRAIN:
			ret = chv_config_set_oden(pctrl, pin, true);
			if (ret)
				return ret;
			break;

		default:
			return -ENOTSUPP;
		}

		dev_dbg(pctrl->dev, "pin %d set config %d arg %u\n", pin,
			param, arg);
	}

	return 0;
}