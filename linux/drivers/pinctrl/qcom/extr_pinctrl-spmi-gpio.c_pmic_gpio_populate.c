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
struct pmic_gpio_state {int /*<<< orphan*/  dev; } ;
struct pmic_gpio_pad {int have_buffer; int num_sources; int lv_mv_type; int out_value; int function; int input_enabled; int output_enabled; int analog_pass; int power_source; int pullup; int dtest_buffer; int strength; int buffer_type; int atest; int is_enabled; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENODEV ; 
 int PMIC_GPIO_LV_MV_ANA_MUX_SEL_MASK ; 
 int PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN ; 
 int PMIC_GPIO_LV_MV_DIG_IN_DTEST_SEL_MASK ; 
 int PMIC_GPIO_LV_MV_OUTPUT_INVERT ; 
 int PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK ; 
#define  PMIC_GPIO_MODE_ANALOG_PASS_THRU 137 
#define  PMIC_GPIO_MODE_DIGITAL_INPUT 136 
#define  PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT 135 
#define  PMIC_GPIO_MODE_DIGITAL_OUTPUT 134 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_IN_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_OUT_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_PULL_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_DIG_VIN_CTL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL ; 
 int PMIC_GPIO_REG_LV_MV_MODE_DIR_MASK ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_MODE_CTL ; 
 int PMIC_GPIO_REG_MODE_DIR_MASK ; 
 int PMIC_GPIO_REG_MODE_DIR_SHIFT ; 
 int PMIC_GPIO_REG_MODE_FUNCTION_MASK ; 
 int PMIC_GPIO_REG_MODE_FUNCTION_SHIFT ; 
 int PMIC_GPIO_REG_MODE_VALUE_SHIFT ; 
 int PMIC_GPIO_REG_OUT_STRENGTH_MASK ; 
 int PMIC_GPIO_REG_OUT_STRENGTH_SHIFT ; 
 int PMIC_GPIO_REG_OUT_TYPE_MASK ; 
 int PMIC_GPIO_REG_OUT_TYPE_SHIFT ; 
 int PMIC_GPIO_REG_PULL_MASK ; 
 int PMIC_GPIO_REG_PULL_SHIFT ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_SUBTYPE ; 
 int /*<<< orphan*/  PMIC_GPIO_REG_TYPE ; 
 int PMIC_GPIO_REG_VIN_MASK ; 
 int PMIC_GPIO_REG_VIN_SHIFT ; 
#define  PMIC_GPIO_SUBTYPE_GPIOC_4CH 133 
#define  PMIC_GPIO_SUBTYPE_GPIOC_8CH 132 
#define  PMIC_GPIO_SUBTYPE_GPIO_4CH 131 
#define  PMIC_GPIO_SUBTYPE_GPIO_8CH 130 
#define  PMIC_GPIO_SUBTYPE_GPIO_LV 129 
#define  PMIC_GPIO_SUBTYPE_GPIO_MV 128 
 int PMIC_GPIO_TYPE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int ffs (int) ; 
 int pmic_gpio_read (struct pmic_gpio_state*,struct pmic_gpio_pad*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmic_gpio_populate(struct pmic_gpio_state *state,
			      struct pmic_gpio_pad *pad)
{
	int type, subtype, val, dir;

	type = pmic_gpio_read(state, pad, PMIC_GPIO_REG_TYPE);
	if (type < 0)
		return type;

	if (type != PMIC_GPIO_TYPE) {
		dev_err(state->dev, "incorrect block type 0x%x at 0x%x\n",
			type, pad->base);
		return -ENODEV;
	}

	subtype = pmic_gpio_read(state, pad, PMIC_GPIO_REG_SUBTYPE);
	if (subtype < 0)
		return subtype;

	switch (subtype) {
	case PMIC_GPIO_SUBTYPE_GPIO_4CH:
		pad->have_buffer = true;
		/* Fall through */
	case PMIC_GPIO_SUBTYPE_GPIOC_4CH:
		pad->num_sources = 4;
		break;
	case PMIC_GPIO_SUBTYPE_GPIO_8CH:
		pad->have_buffer = true;
		/* Fall through */
	case PMIC_GPIO_SUBTYPE_GPIOC_8CH:
		pad->num_sources = 8;
		break;
	case PMIC_GPIO_SUBTYPE_GPIO_LV:
		pad->num_sources = 1;
		pad->have_buffer = true;
		pad->lv_mv_type = true;
		break;
	case PMIC_GPIO_SUBTYPE_GPIO_MV:
		pad->num_sources = 2;
		pad->have_buffer = true;
		pad->lv_mv_type = true;
		break;
	default:
		dev_err(state->dev, "unknown GPIO type 0x%x\n", subtype);
		return -ENODEV;
	}

	if (pad->lv_mv_type) {
		val = pmic_gpio_read(state, pad,
				PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL);
		if (val < 0)
			return val;

		pad->out_value = !!(val & PMIC_GPIO_LV_MV_OUTPUT_INVERT);
		pad->function = val & PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK;

		val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_MODE_CTL);
		if (val < 0)
			return val;

		dir = val & PMIC_GPIO_REG_LV_MV_MODE_DIR_MASK;
	} else {
		val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_MODE_CTL);
		if (val < 0)
			return val;

		pad->out_value = val & PMIC_GPIO_REG_MODE_VALUE_SHIFT;

		dir = val >> PMIC_GPIO_REG_MODE_DIR_SHIFT;
		dir &= PMIC_GPIO_REG_MODE_DIR_MASK;
		pad->function = val >> PMIC_GPIO_REG_MODE_FUNCTION_SHIFT;
		pad->function &= PMIC_GPIO_REG_MODE_FUNCTION_MASK;
	}

	switch (dir) {
	case PMIC_GPIO_MODE_DIGITAL_INPUT:
		pad->input_enabled = true;
		pad->output_enabled = false;
		break;
	case PMIC_GPIO_MODE_DIGITAL_OUTPUT:
		pad->input_enabled = false;
		pad->output_enabled = true;
		break;
	case PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT:
		pad->input_enabled = true;
		pad->output_enabled = true;
		break;
	case PMIC_GPIO_MODE_ANALOG_PASS_THRU:
		if (!pad->lv_mv_type)
			return -ENODEV;
		pad->analog_pass = true;
		break;
	default:
		dev_err(state->dev, "unknown GPIO direction\n");
		return -ENODEV;
	}

	val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_DIG_VIN_CTL);
	if (val < 0)
		return val;

	pad->power_source = val >> PMIC_GPIO_REG_VIN_SHIFT;
	pad->power_source &= PMIC_GPIO_REG_VIN_MASK;

	val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_DIG_PULL_CTL);
	if (val < 0)
		return val;

	pad->pullup = val >> PMIC_GPIO_REG_PULL_SHIFT;
	pad->pullup &= PMIC_GPIO_REG_PULL_MASK;

	val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_DIG_IN_CTL);
	if (val < 0)
		return val;

	if (pad->lv_mv_type && (val & PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN))
		pad->dtest_buffer =
			(val & PMIC_GPIO_LV_MV_DIG_IN_DTEST_SEL_MASK) + 1;
	else if (!pad->lv_mv_type)
		pad->dtest_buffer = ffs(val);
	else
		pad->dtest_buffer = 0;

	val = pmic_gpio_read(state, pad, PMIC_GPIO_REG_DIG_OUT_CTL);
	if (val < 0)
		return val;

	pad->strength = val >> PMIC_GPIO_REG_OUT_STRENGTH_SHIFT;
	pad->strength &= PMIC_GPIO_REG_OUT_STRENGTH_MASK;

	pad->buffer_type = val >> PMIC_GPIO_REG_OUT_TYPE_SHIFT;
	pad->buffer_type &= PMIC_GPIO_REG_OUT_TYPE_MASK;

	if (pad->lv_mv_type) {
		val = pmic_gpio_read(state, pad,
				PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL);
		if (val < 0)
			return val;
		pad->atest = (val & PMIC_GPIO_LV_MV_ANA_MUX_SEL_MASK) + 1;
	}

	/* Pin could be disabled with PIN_CONFIG_BIAS_HIGH_IMPEDANCE */
	pad->is_enabled = true;
	return 0;
}