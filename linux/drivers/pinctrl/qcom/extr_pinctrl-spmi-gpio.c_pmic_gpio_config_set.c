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
struct pmic_gpio_state {int dummy; } ;
struct pmic_gpio_pad {int is_enabled; unsigned int buffer_type; unsigned int pullup; unsigned int num_sources; unsigned int power_source; int input_enabled; int output_enabled; unsigned int out_value; unsigned int strength; unsigned int atest; int analog_pass; unsigned int dtest_buffer; unsigned int function; scalar_t__ lv_mv_type; int /*<<< orphan*/  have_buffer; } ;
struct pinctrl_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {struct pmic_gpio_pad* drv_data; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
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
 unsigned int PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN ; 
 unsigned int PMIC_GPIO_LV_MV_OUTPUT_INVERT_SHIFT ; 
 unsigned int PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK ; 
 unsigned int PMIC_GPIO_MODE_ANALOG_PASS_THRU ; 
 unsigned int PMIC_GPIO_MODE_DIGITAL_INPUT ; 
 unsigned int PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT ; 
 unsigned int PMIC_GPIO_MODE_DIGITAL_OUTPUT ; 
 unsigned int PMIC_GPIO_OUT_BUF_CMOS ; 
 unsigned int PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS ; 
 unsigned int PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS ; 
 void* PMIC_GPIO_PULL_DISABLE ; 
 unsigned int PMIC_GPIO_PULL_DOWN ; 
 unsigned int PMIC_GPIO_PULL_UP_1P5_30 ; 
 unsigned int PMIC_GPIO_PULL_UP_30 ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_IN_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_OUT_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_PULL_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_VIN_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_EN_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL ; 
 unsigned int PMIC_GPIO_REG_MASTER_EN_SHIFT ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_MODE_CTL ; 
 unsigned int PMIC_GPIO_REG_MODE_DIR_SHIFT ; 
 unsigned int PMIC_GPIO_REG_MODE_FUNCTION_SHIFT ; 
 unsigned int PMIC_GPIO_REG_MODE_VALUE_SHIFT ; 
 unsigned int PMIC_GPIO_REG_OUT_STRENGTH_SHIFT ; 
 unsigned int PMIC_GPIO_REG_OUT_TYPE_SHIFT ; 
 unsigned int PMIC_GPIO_REG_PULL_SHIFT ; 
 unsigned int PMIC_GPIO_REG_VIN_SHIFT ; 
 unsigned int PMIC_GPIO_STRENGTH_LOW ; 
 unsigned int pinconf_to_config_argument (unsigned long) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct pmic_gpio_state* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int pmic_gpio_write (struct pmic_gpio_state*,struct pmic_gpio_pad*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pmic_gpio_config_set(struct pinctrl_dev *pctldev, unsigned int pin,
				unsigned long *configs, unsigned nconfs)
{
	struct pmic_gpio_state *state = pinctrl_dev_get_drvdata(pctldev);
	struct pmic_gpio_pad *pad;
	unsigned param, arg;
	unsigned int val;
	int i, ret;

	pad = pctldev->desc->pins[pin].drv_data;

	pad->is_enabled = true;
	for (i = 0; i < nconfs; i++) {
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		switch (param) {
		case PIN_CONFIG_DRIVE_PUSH_PULL:
			pad->buffer_type = PMIC_GPIO_OUT_BUF_CMOS;
			break;
		case PIN_CONFIG_DRIVE_OPEN_DRAIN:
			if (!pad->have_buffer)
				return -EINVAL;
			pad->buffer_type = PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS;
			break;
		case PIN_CONFIG_DRIVE_OPEN_SOURCE:
			if (!pad->have_buffer)
				return -EINVAL;
			pad->buffer_type = PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS;
			break;
		case PIN_CONFIG_BIAS_DISABLE:
			pad->pullup = PMIC_GPIO_PULL_DISABLE;
			break;
		case PIN_CONFIG_BIAS_PULL_UP:
			pad->pullup = PMIC_GPIO_PULL_UP_30;
			break;
		case PIN_CONFIG_BIAS_PULL_DOWN:
			if (arg)
				pad->pullup = PMIC_GPIO_PULL_DOWN;
			else
				pad->pullup = PMIC_GPIO_PULL_DISABLE;
			break;
		case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pad->is_enabled = false;
			break;
		case PIN_CONFIG_POWER_SOURCE:
			if (arg >= pad->num_sources)
				return -EINVAL;
			pad->power_source = arg;
			break;
		case PIN_CONFIG_INPUT_ENABLE:
			pad->input_enabled = arg ? true : false;
			break;
		case PIN_CONFIG_OUTPUT:
			pad->output_enabled = true;
			pad->out_value = arg;
			break;
		case PMIC_GPIO_CONF_PULL_UP:
			if (arg > PMIC_GPIO_PULL_UP_1P5_30)
				return -EINVAL;
			pad->pullup = arg;
			break;
		case PMIC_GPIO_CONF_STRENGTH:
			if (arg > PMIC_GPIO_STRENGTH_LOW)
				return -EINVAL;
			pad->strength = arg;
			break;
		case PMIC_GPIO_CONF_ATEST:
			if (!pad->lv_mv_type || arg > 4)
				return -EINVAL;
			pad->atest = arg;
			break;
		case PMIC_GPIO_CONF_ANALOG_PASS:
			if (!pad->lv_mv_type)
				return -EINVAL;
			pad->analog_pass = true;
			break;
		case PMIC_GPIO_CONF_DTEST_BUFFER:
			if (arg > 4)
				return -EINVAL;
			pad->dtest_buffer = arg;
			break;
		default:
			return -EINVAL;
		}
	}

	val = pad->power_source << PMIC_GPIO_REG_VIN_SHIFT;

	ret = pmic_gpio_write(state, pad, PMIC_GPIO_REG_DIG_VIN_CTL, val);
	if (ret < 0)
		return ret;

	val = pad->pullup << PMIC_GPIO_REG_PULL_SHIFT;

	ret = pmic_gpio_write(state, pad, PMIC_GPIO_REG_DIG_PULL_CTL, val);
	if (ret < 0)
		return ret;

	val = pad->buffer_type << PMIC_GPIO_REG_OUT_TYPE_SHIFT;
	val |= pad->strength << PMIC_GPIO_REG_OUT_STRENGTH_SHIFT;

	ret = pmic_gpio_write(state, pad, PMIC_GPIO_REG_DIG_OUT_CTL, val);
	if (ret < 0)
		return ret;

	if (pad->dtest_buffer == 0) {
		val = 0;
	} else {
		if (pad->lv_mv_type) {
			val = pad->dtest_buffer - 1;
			val |= PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN;
		} else {
			val = BIT(pad->dtest_buffer - 1);
		}
	}
	ret = pmic_gpio_write(state, pad, PMIC_GPIO_REG_DIG_IN_CTL, val);
	if (ret < 0)
		return ret;

	if (pad->analog_pass)
		val = PMIC_GPIO_MODE_ANALOG_PASS_THRU;
	else if (pad->output_enabled && pad->input_enabled)
		val = PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT;
	else if (pad->output_enabled)
		val = PMIC_GPIO_MODE_DIGITAL_OUTPUT;
	else
		val = PMIC_GPIO_MODE_DIGITAL_INPUT;

	if (pad->lv_mv_type) {
		ret = pmic_gpio_write(state, pad,
				PMIC_GPIO_REG_MODE_CTL, val);
		if (ret < 0)
			return ret;

		val = pad->atest - 1;
		ret = pmic_gpio_write(state, pad,
				PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL, val);
		if (ret < 0)
			return ret;

		val = pad->out_value
			<< PMIC_GPIO_LV_MV_OUTPUT_INVERT_SHIFT;
		val |= pad->function
			& PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK;
		ret = pmic_gpio_write(state, pad,
			PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL, val);
		if (ret < 0)
			return ret;
	} else {
		val = val << PMIC_GPIO_REG_MODE_DIR_SHIFT;
		val |= pad->function << PMIC_GPIO_REG_MODE_FUNCTION_SHIFT;
		val |= pad->out_value & PMIC_GPIO_REG_MODE_VALUE_SHIFT;

		ret = pmic_gpio_write(state, pad, PMIC_GPIO_REG_MODE_CTL, val);
		if (ret < 0)
			return ret;
	}

	val = pad->is_enabled << PMIC_GPIO_REG_MASTER_EN_SHIFT;

	ret = pmic_gpio_write(state, pad, PMIC_GPIO_REG_EN_CTL, val);

	return ret;
}