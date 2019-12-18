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
struct pmic_gpio_pad {unsigned int pullup; unsigned int power_source; unsigned int out_value; unsigned int strength; unsigned int atest; unsigned int analog_pass; unsigned int dtest_buffer; int /*<<< orphan*/  input_enabled; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  buffer_type; } ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {struct pmic_gpio_pad* drv_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_BIAS_DISABLE 142 
#define  PIN_CONFIG_BIAS_HIGH_IMPEDANCE 141 
#define  PIN_CONFIG_BIAS_PULL_DOWN 140 
#define  PIN_CONFIG_BIAS_PULL_UP 139 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 138 
#define  PIN_CONFIG_DRIVE_OPEN_SOURCE 137 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 136 
#define  PIN_CONFIG_INPUT_ENABLE 135 
#define  PIN_CONFIG_OUTPUT 134 
#define  PIN_CONFIG_POWER_SOURCE 133 
#define  PMIC_GPIO_CONF_ANALOG_PASS 132 
#define  PMIC_GPIO_CONF_ATEST 131 
#define  PMIC_GPIO_CONF_DTEST_BUFFER 130 
#define  PMIC_GPIO_CONF_PULL_UP 129 
#define  PMIC_GPIO_CONF_STRENGTH 128 
 int /*<<< orphan*/  PMIC_GPIO_OUT_BUF_CMOS ; 
 int /*<<< orphan*/  PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS ; 
 int /*<<< orphan*/  PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS ; 
 unsigned int PMIC_GPIO_PULL_DISABLE ; 
 unsigned int PMIC_GPIO_PULL_DOWN ; 
 unsigned int PMIC_GPIO_PULL_UP_30 ; 
 unsigned long pinconf_to_config_packed (unsigned int,unsigned int) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int pmic_gpio_config_get(struct pinctrl_dev *pctldev,
				unsigned int pin, unsigned long *config)
{
	unsigned param = pinconf_to_config_param(*config);
	struct pmic_gpio_pad *pad;
	unsigned arg;

	pad = pctldev->desc->pins[pin].drv_data;

	switch (param) {
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		if (pad->buffer_type != PMIC_GPIO_OUT_BUF_CMOS)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		if (pad->buffer_type != PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_DRIVE_OPEN_SOURCE:
		if (pad->buffer_type != PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (pad->pullup != PMIC_GPIO_PULL_DOWN)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_DISABLE:
		if (pad->pullup != PMIC_GPIO_PULL_DISABLE)
			return -EINVAL;
		arg = 1;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		if (pad->pullup != PMIC_GPIO_PULL_UP_30)
			return -EINVAL;
		arg = 1;
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
	case PMIC_GPIO_CONF_PULL_UP:
		arg = pad->pullup;
		break;
	case PMIC_GPIO_CONF_STRENGTH:
		arg = pad->strength;
		break;
	case PMIC_GPIO_CONF_ATEST:
		arg = pad->atest;
		break;
	case PMIC_GPIO_CONF_ANALOG_PASS:
		arg = pad->analog_pass;
		break;
	case PMIC_GPIO_CONF_DTEST_BUFFER:
		arg = pad->dtest_buffer;
		break;
	default:
		return -EINVAL;
	}

	*config = pinconf_to_config_packed(param, arg);
	return 0;
}