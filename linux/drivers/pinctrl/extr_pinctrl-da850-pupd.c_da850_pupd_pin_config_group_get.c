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
typedef  int u32 ;
typedef  int u16 ;
struct pinctrl_dev {int dummy; } ;
struct da850_pupd_data {scalar_t__ base; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ DA850_PUPD_ENA ; 
 scalar_t__ DA850_PUPD_SEL ; 
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 130 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct da850_pupd_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int da850_pupd_pin_config_group_get(struct pinctrl_dev *pctldev,
					   unsigned int selector,
					   unsigned long *config)
{
	struct da850_pupd_data *data = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	u32 val;
	u16 arg;

	val = readl(data->base + DA850_PUPD_ENA);
	arg = !!(~val & BIT(selector));

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (arg) {
			/* bias is disabled */
			arg = 0;
			break;
		}
		val = readl(data->base + DA850_PUPD_SEL);
		if (param == PIN_CONFIG_BIAS_PULL_DOWN)
			val = ~val;
		arg = !!(val & BIT(selector));
		break;
	default:
		return -EINVAL;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}