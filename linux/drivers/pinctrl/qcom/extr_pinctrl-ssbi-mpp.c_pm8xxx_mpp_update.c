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
typedef  unsigned int u8 ;
struct pm8xxx_pin_data {int mode; unsigned int dtest; int pullup; unsigned int output_value; unsigned int power_source; unsigned int aout_level; unsigned int amux; int drive_strength; int /*<<< orphan*/  reg; int /*<<< orphan*/  paired; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  high_z; } ;
struct pm8xxx_mpp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int EINVAL ; 
#define  PM8XXX_MPP_ANALOG 130 
 unsigned int PM8XXX_MPP_BI_PULLUP_10KOHM ; 
 unsigned int PM8XXX_MPP_BI_PULLUP_1KOHM ; 
 unsigned int PM8XXX_MPP_BI_PULLUP_30KOHM ; 
 unsigned int PM8XXX_MPP_BI_PULLUP_OPEN ; 
#define  PM8XXX_MPP_DIGITAL 129 
 unsigned int PM8XXX_MPP_DIN_TO_INT ; 
#define  PM8XXX_MPP_SINK 128 
 unsigned int PM8XXX_MPP_TYPE_A_INPUT ; 
 unsigned int PM8XXX_MPP_TYPE_A_OUTPUT ; 
 unsigned int PM8XXX_MPP_TYPE_DTEST_OUTPUT ; 
 unsigned int PM8XXX_MPP_TYPE_DTEST_SINK ; 
 unsigned int PM8XXX_MPP_TYPE_D_BI_DIR ; 
 unsigned int PM8XXX_MPP_TYPE_D_INPUT ; 
 unsigned int PM8XXX_MPP_TYPE_D_OUTPUT ; 
 unsigned int PM8XXX_MPP_TYPE_SINK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pm8xxx_mpp_update(struct pm8xxx_mpp *pctrl,
			     struct pm8xxx_pin_data *pin)
{
	unsigned level;
	unsigned ctrl;
	unsigned type;
	int ret;
	u8 val;

	switch (pin->mode) {
	case PM8XXX_MPP_DIGITAL:
		if (pin->dtest) {
			type = PM8XXX_MPP_TYPE_DTEST_OUTPUT;
			ctrl = pin->dtest - 1;
		} else if (pin->input && pin->output) {
			type = PM8XXX_MPP_TYPE_D_BI_DIR;
			if (pin->high_z)
				ctrl = PM8XXX_MPP_BI_PULLUP_OPEN;
			else if (pin->pullup == 600)
				ctrl = PM8XXX_MPP_BI_PULLUP_1KOHM;
			else if (pin->pullup == 10000)
				ctrl = PM8XXX_MPP_BI_PULLUP_10KOHM;
			else
				ctrl = PM8XXX_MPP_BI_PULLUP_30KOHM;
		} else if (pin->input) {
			type = PM8XXX_MPP_TYPE_D_INPUT;
			if (pin->dtest)
				ctrl = pin->dtest;
			else
				ctrl = PM8XXX_MPP_DIN_TO_INT;
		} else {
			type = PM8XXX_MPP_TYPE_D_OUTPUT;
			ctrl = !!pin->output_value;
			if (pin->paired)
				ctrl |= BIT(1);
		}

		level = pin->power_source;
		break;
	case PM8XXX_MPP_ANALOG:
		if (pin->output) {
			type = PM8XXX_MPP_TYPE_A_OUTPUT;
			level = pin->aout_level;
			ctrl = pin->output_value;
			if (pin->paired)
				ctrl |= BIT(1);
		} else {
			type = PM8XXX_MPP_TYPE_A_INPUT;
			level = pin->amux;
			ctrl = 0;
		}
		break;
	case PM8XXX_MPP_SINK:
		level = (pin->drive_strength / 5) - 1;
		if (pin->dtest) {
			type = PM8XXX_MPP_TYPE_DTEST_SINK;
			ctrl = pin->dtest - 1;
		} else {
			type = PM8XXX_MPP_TYPE_SINK;
			ctrl = pin->output_value;
			if (pin->paired)
				ctrl |= BIT(1);
		}
		break;
	default:
		return -EINVAL;
	}

	val = type << 5 | level << 2 | ctrl;
	ret = regmap_write(pctrl->regmap, pin->reg, val);
	if (ret)
		dev_err(pctrl->dev, "failed to write register\n");

	return ret;
}