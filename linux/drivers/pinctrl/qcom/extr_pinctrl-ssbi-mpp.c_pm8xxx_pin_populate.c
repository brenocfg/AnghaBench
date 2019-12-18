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
typedef  unsigned int val ;
struct pm8xxx_pin_data {int input; unsigned int power_source; unsigned int dtest; int output; int output_value; int paired; int pullup; int high_z; unsigned int amux; unsigned int aout_level; int drive_strength; void* mode; int /*<<< orphan*/  reg; } ;
struct pm8xxx_mpp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 void* PM8XXX_MPP_ANALOG ; 
#define  PM8XXX_MPP_BI_PULLUP_10KOHM 139 
#define  PM8XXX_MPP_BI_PULLUP_1KOHM 138 
#define  PM8XXX_MPP_BI_PULLUP_30KOHM 137 
#define  PM8XXX_MPP_BI_PULLUP_OPEN 136 
 void* PM8XXX_MPP_DIGITAL ; 
 void* PM8XXX_MPP_SINK ; 
#define  PM8XXX_MPP_TYPE_A_INPUT 135 
#define  PM8XXX_MPP_TYPE_A_OUTPUT 134 
#define  PM8XXX_MPP_TYPE_DTEST_OUTPUT 133 
#define  PM8XXX_MPP_TYPE_DTEST_SINK 132 
#define  PM8XXX_MPP_TYPE_D_BI_DIR 131 
#define  PM8XXX_MPP_TYPE_D_INPUT 130 
#define  PM8XXX_MPP_TYPE_D_OUTPUT 129 
#define  PM8XXX_MPP_TYPE_SINK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pm8xxx_pin_populate(struct pm8xxx_mpp *pctrl,
			       struct pm8xxx_pin_data *pin)
{
	unsigned int val;
	unsigned level;
	unsigned ctrl;
	unsigned type;
	int ret;

	ret = regmap_read(pctrl->regmap, pin->reg, &val);
	if (ret) {
		dev_err(pctrl->dev, "failed to read register\n");
		return ret;
	}

	type = (val >> 5) & 7;
	level = (val >> 2) & 7;
	ctrl = (val) & 3;

	switch (type) {
	case PM8XXX_MPP_TYPE_D_INPUT:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->input = true;
		pin->power_source = level;
		pin->dtest = ctrl;
		break;
	case PM8XXX_MPP_TYPE_D_OUTPUT:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->output = true;
		pin->power_source = level;
		pin->output_value = !!(ctrl & BIT(0));
		pin->paired = !!(ctrl & BIT(1));
		break;
	case PM8XXX_MPP_TYPE_D_BI_DIR:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->input = true;
		pin->output = true;
		pin->power_source = level;
		switch (ctrl) {
		case PM8XXX_MPP_BI_PULLUP_1KOHM:
			pin->pullup = 600;
			break;
		case PM8XXX_MPP_BI_PULLUP_OPEN:
			pin->high_z = true;
			break;
		case PM8XXX_MPP_BI_PULLUP_10KOHM:
			pin->pullup = 10000;
			break;
		case PM8XXX_MPP_BI_PULLUP_30KOHM:
			pin->pullup = 30000;
			break;
		}
		break;
	case PM8XXX_MPP_TYPE_A_INPUT:
		pin->mode = PM8XXX_MPP_ANALOG;
		pin->input = true;
		pin->amux = level;
		break;
	case PM8XXX_MPP_TYPE_A_OUTPUT:
		pin->mode = PM8XXX_MPP_ANALOG;
		pin->output = true;
		pin->aout_level = level;
		pin->output_value = !!(ctrl & BIT(0));
		pin->paired = !!(ctrl & BIT(1));
		break;
	case PM8XXX_MPP_TYPE_SINK:
		pin->mode = PM8XXX_MPP_SINK;
		pin->drive_strength = 5 * (level + 1);
		pin->output_value = !!(ctrl & BIT(0));
		pin->paired = !!(ctrl & BIT(1));
		break;
	case PM8XXX_MPP_TYPE_DTEST_SINK:
		pin->mode = PM8XXX_MPP_SINK;
		pin->dtest = ctrl + 1;
		pin->drive_strength = 5 * (level + 1);
		break;
	case PM8XXX_MPP_TYPE_DTEST_OUTPUT:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->power_source = level;
		if (ctrl >= 1)
			pin->dtest = ctrl;
		break;
	}

	return 0;
}