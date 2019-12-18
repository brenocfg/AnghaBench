#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmic_mpp_pad {unsigned int power_source; unsigned int out_value; unsigned int dtest; unsigned int amux_input; unsigned int drive_strength; unsigned int aout_level; int /*<<< orphan*/  paired; int /*<<< orphan*/  input_enabled; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  pullup; } ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {struct pmic_mpp_pad* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 141 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 140 
#define  PIN_CONFIG_BIAS_PULL_UP 139 
#define  PIN_CONFIG_DRIVE_STRENGTH 138 
#define  PIN_CONFIG_INPUT_ENABLE 137 
#define  PIN_CONFIG_OUTPUT 136 
#define  PIN_CONFIG_POWER_SOURCE 135 
#define  PMIC_MPP_CONF_AMUX_ROUTE 134 
#define  PMIC_MPP_CONF_ANALOG_LEVEL 133 
#define  PMIC_MPP_CONF_DTEST_SELECTOR 132 
#define  PMIC_MPP_CONF_PAIRED 131 
#define  PMIC_MPP_PULL_UP_0P6KOHM 130 
#define  PMIC_MPP_PULL_UP_10KOHM 129 
#define  PMIC_MPP_PULL_UP_30KOHM 128 
 int /*<<< orphan*/  PMIC_MPP_PULL_UP_OPEN ; 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int pmic_mpp_config_get(struct pinctrl_dev *pctldev,
			       unsigned int pin, unsigned long *config)
{
	unsigned param = pinconf_to_config_param(*config);
	struct pmic_mpp_pad *pad;
	unsigned arg = 0;

	pad = pctldev->desc->pins[pin].drv_data;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (pad->pullup != PMIC_MPP_PULL_UP_OPEN)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		switch (pad->pullup) {
		case PMIC_MPP_PULL_UP_0P6KOHM:
			arg = 600;
			break;
		case PMIC_MPP_PULL_UP_10KOHM:
			arg = 10000;
			break;
		case PMIC_MPP_PULL_UP_30KOHM:
			arg = 30000;
			break;
		default:
			return -EINVAL;
		}
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		if (pad->is_enabled)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_POWER_SOURCE:
		arg = pad->power_source;
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		if (!pad->input_enabled)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_OUTPUT:
		arg = pad->out_value;
		break;
	case PMIC_MPP_CONF_DTEST_SELECTOR:
		arg = pad->dtest;
		break;
	case PMIC_MPP_CONF_AMUX_ROUTE:
		arg = pad->amux_input;
		break;
	case PMIC_MPP_CONF_PAIRED:
		if (!pad->paired)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		arg = pad->drive_strength;
		break;
	case PMIC_MPP_CONF_ANALOG_LEVEL:
		arg = pad->aout_level;
		break;
	default:
		return -EINVAL;
	}

	/* Convert register value to pinconf value */
	*config = pinconf_to_config_packed(param, arg);
	return 0;
}