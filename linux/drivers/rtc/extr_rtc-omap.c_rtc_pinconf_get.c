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
typedef  int /*<<< orphan*/  u16 ;
struct pinctrl_dev {int dummy; } ;
struct omap_rtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int OMAP_RTC_PMIC_EXT_WKUP_EN (unsigned int) ; 
 int OMAP_RTC_PMIC_EXT_WKUP_POL (unsigned int) ; 
 int /*<<< orphan*/  OMAP_RTC_PMIC_REG ; 
#define  PIN_CONFIG_ACTIVE_HIGH 129 
#define  PIN_CONFIG_INPUT_ENABLE 128 
 unsigned long pinconf_to_config_packed (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct omap_rtc* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int rtc_readl (struct omap_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtc_pinconf_get(struct pinctrl_dev *pctldev,
			unsigned int pin, unsigned long *config)
{
	struct omap_rtc *rtc = pinctrl_dev_get_drvdata(pctldev);
	unsigned int param = pinconf_to_config_param(*config);
	u32 val;
	u16 arg = 0;

	val = rtc_readl(rtc, OMAP_RTC_PMIC_REG);

	switch (param) {
	case PIN_CONFIG_INPUT_ENABLE:
		if (!(val & OMAP_RTC_PMIC_EXT_WKUP_EN(pin)))
			return -EINVAL;
		break;
	case PIN_CONFIG_ACTIVE_HIGH:
		if (val & OMAP_RTC_PMIC_EXT_WKUP_POL(pin))
			return -EINVAL;
		break;
	default:
		return -ENOTSUPP;
	};

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}