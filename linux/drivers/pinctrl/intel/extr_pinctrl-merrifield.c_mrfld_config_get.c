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
struct mrfld_pinctrl {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int BUFCFG_OD_EN ; 
 int BUFCFG_PD_EN ; 
#define  BUFCFG_PUPD_VAL_20K 136 
#define  BUFCFG_PUPD_VAL_2K 135 
#define  BUFCFG_PUPD_VAL_50K 134 
#define  BUFCFG_PUPD_VAL_910 133 
 int BUFCFG_PUPD_VAL_MASK ; 
 int BUFCFG_PUPD_VAL_SHIFT ; 
 int BUFCFG_PU_EN ; 
 int BUFCFG_Px_EN_MASK ; 
 int BUFCFG_SLEWSEL ; 
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_DISABLE 132 
#define  PIN_CONFIG_BIAS_PULL_DOWN 131 
#define  PIN_CONFIG_BIAS_PULL_UP 130 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int mrfld_read_bufcfg (struct mrfld_pinctrl*,unsigned int,int*) ; 
 unsigned long pinconf_to_config_packed (int,int) ; 
 int pinconf_to_config_param (unsigned long) ; 
 struct mrfld_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int mrfld_config_get(struct pinctrl_dev *pctldev, unsigned int pin,
			    unsigned long *config)
{
	struct mrfld_pinctrl *mp = pinctrl_dev_get_drvdata(pctldev);
	enum pin_config_param param = pinconf_to_config_param(*config);
	u32 value, term;
	u16 arg = 0;
	int ret;

	ret = mrfld_read_bufcfg(mp, pin, &value);
	if (ret)
		return -ENOTSUPP;

	term = (value & BUFCFG_PUPD_VAL_MASK) >> BUFCFG_PUPD_VAL_SHIFT;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (value & BUFCFG_Px_EN_MASK)
			return -EINVAL;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
		if ((value & BUFCFG_Px_EN_MASK) != BUFCFG_PU_EN)
			return -EINVAL;

		switch (term) {
		case BUFCFG_PUPD_VAL_910:
			arg = 910;
			break;
		case BUFCFG_PUPD_VAL_2K:
			arg = 2000;
			break;
		case BUFCFG_PUPD_VAL_20K:
			arg = 20000;
			break;
		case BUFCFG_PUPD_VAL_50K:
			arg = 50000;
			break;
		}

		break;

	case PIN_CONFIG_BIAS_PULL_DOWN:
		if ((value & BUFCFG_Px_EN_MASK) != BUFCFG_PD_EN)
			return -EINVAL;

		switch (term) {
		case BUFCFG_PUPD_VAL_910:
			arg = 910;
			break;
		case BUFCFG_PUPD_VAL_2K:
			arg = 2000;
			break;
		case BUFCFG_PUPD_VAL_20K:
			arg = 20000;
			break;
		case BUFCFG_PUPD_VAL_50K:
			arg = 50000;
			break;
		}

		break;

	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (!(value & BUFCFG_OD_EN))
			return -EINVAL;
		break;

	case PIN_CONFIG_SLEW_RATE:
		if (!(value & BUFCFG_SLEWSEL))
			arg = 0;
		else
			arg = 1;
		break;

	default:
		return -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(param, arg);
	return 0;
}