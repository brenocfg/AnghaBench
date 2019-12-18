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
struct pm8xxx_pin_data {unsigned int pull_up_strength; int mode; unsigned int output_value; unsigned int power_source; unsigned int output_strength; int /*<<< orphan*/  open_drain; int /*<<< orphan*/  disable; int /*<<< orphan*/  bias; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_gpio {TYPE_2__ desc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 138 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 137 
#define  PIN_CONFIG_BIAS_PULL_DOWN 136 
#define  PIN_CONFIG_BIAS_PULL_UP 135 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 134 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 133 
#define  PIN_CONFIG_INPUT_ENABLE 132 
#define  PIN_CONFIG_OUTPUT 131 
#define  PIN_CONFIG_POWER_SOURCE 130 
 int /*<<< orphan*/  PM8XXX_GPIO_BIAS_NP ; 
 int /*<<< orphan*/  PM8XXX_GPIO_BIAS_PD ; 
 int /*<<< orphan*/  PM8XXX_GPIO_BIAS_PU_1P5_30 ; 
 int PM8XXX_GPIO_MODE_INPUT ; 
 int PM8XXX_GPIO_MODE_OUTPUT ; 
#define  PM8XXX_QCOM_DRIVE_STRENGH 129 
#define  PM8XXX_QCOM_PULL_UP_STRENGTH 128 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct pm8xxx_gpio* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int pm8xxx_pin_config_get(struct pinctrl_dev *pctldev,
				 unsigned int offset,
				 unsigned long *config)
{
	struct pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	unsigned param = pinconf_to_config_param(*config);
	unsigned arg;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		if (pin->bias != PM8XXX_GPIO_BIAS_NP)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (pin->bias != PM8XXX_GPIO_BIAS_PD)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		if (pin->bias > PM8XXX_GPIO_BIAS_PU_1P5_30)
			return -EINVAL;
		arg = 1;
		break;
	case PM8XXX_QCOM_PULL_UP_STRENGTH:
		arg = pin->pull_up_strength;
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		if (!pin->disable)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		if (pin->mode != PM8XXX_GPIO_MODE_INPUT)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_OUTPUT:
		if (pin->mode & PM8XXX_GPIO_MODE_OUTPUT)
			arg = pin->output_value;
		else
			arg = 0;
		break;
	case PIN_CONFIG_POWER_SOURCE:
		arg = pin->power_source;
		break;
	case PM8XXX_QCOM_DRIVE_STRENGH:
		arg = pin->output_strength;
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		if (pin->open_drain)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (!pin->open_drain)
			return -EINVAL;
		arg = 1;
		break;
	default:
		return -EINVAL;
	}

	*config = pinconf_to_config_packed(param, arg);

	return 0;
}