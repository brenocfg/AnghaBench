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
union power_supply_propval {int intval; } ;
typedef  int u8 ;
struct twl4030_bci {int ac_cur; int usb_cur_target; int /*<<< orphan*/  ac_is_active; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_2__* desc; TYPE_1__ dev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 132 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 void* POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 scalar_t__ POWER_SUPPLY_TYPE_USB ; 
 int /*<<< orphan*/  TWL4030_BCICTL1 ; 
 int /*<<< orphan*/  TWL4030_BCIIREF1 ; 
 int /*<<< orphan*/  TWL4030_BCIMDEN ; 
 int /*<<< orphan*/  TWL4030_BCIVAC ; 
 int /*<<< orphan*/  TWL4030_BCIVBUS ; 
 int TWL4030_CGAIN ; 
 int TWL4030_MSTATEC_AC ; 
 int TWL4030_MSTATEC_QUICK1 ; 
 int TWL4030_MSTATEC_USB ; 
 struct twl4030_bci* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regval2ua (int,int) ; 
 int twl4030_bci_read (int /*<<< orphan*/ ,int*) ; 
 void* twl4030_bci_state_to_status (int) ; 
 int twl4030_charger_get_current () ; 
 void* twl4030bci_read_adc_val (int /*<<< orphan*/ ) ; 
 int twl4030bci_state (struct twl4030_bci*) ; 

__attribute__((used)) static int twl4030_bci_get_property(struct power_supply *psy,
				    enum power_supply_property psp,
				    union power_supply_propval *val)
{
	struct twl4030_bci *bci = dev_get_drvdata(psy->dev.parent);
	int is_charging;
	int state;
	int ret;

	state = twl4030bci_state(bci);
	if (state < 0)
		return state;

	if (psy->desc->type == POWER_SUPPLY_TYPE_USB)
		is_charging = state & TWL4030_MSTATEC_USB;
	else
		is_charging = state & TWL4030_MSTATEC_AC;
	if (!is_charging) {
		u8 s;
		ret = twl4030_bci_read(TWL4030_BCIMDEN, &s);
		if (ret < 0)
			return ret;
		if (psy->desc->type == POWER_SUPPLY_TYPE_USB)
			is_charging = s & 1;
		else
			is_charging = s & 2;
		if (is_charging)
			/* A little white lie */
			state = TWL4030_MSTATEC_QUICK1;
	}

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (is_charging)
			val->intval = twl4030_bci_state_to_status(state);
		else
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		/* charging must be active for meaningful result */
		if (!is_charging)
			return -ENODATA;
		if (psy->desc->type == POWER_SUPPLY_TYPE_USB) {
			ret = twl4030bci_read_adc_val(TWL4030_BCIVBUS);
			if (ret < 0)
				return ret;
			/* BCIVBUS uses ADCIN8, 7/1023 V/step */
			val->intval = ret * 6843;
		} else {
			ret = twl4030bci_read_adc_val(TWL4030_BCIVAC);
			if (ret < 0)
				return ret;
			/* BCIVAC uses ADCIN11, 10/1023 V/step */
			val->intval = ret * 9775;
		}
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (!is_charging)
			return -ENODATA;
		/* current measurement is shared between AC and USB */
		ret = twl4030_charger_get_current();
		if (ret < 0)
			return ret;
		val->intval = ret;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = is_charging &&
			twl4030_bci_state_to_status(state) !=
				POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		val->intval = -1;
		if (psy->desc->type != POWER_SUPPLY_TYPE_USB) {
			if (!bci->ac_is_active)
				val->intval = bci->ac_cur;
		} else {
			if (bci->ac_is_active)
				val->intval = bci->usb_cur_target;
		}
		if (val->intval < 0) {
			u8 bcictl1;

			val->intval = twl4030bci_read_adc_val(TWL4030_BCIIREF1);
			if (val->intval < 0)
				return val->intval;
			ret = twl4030_bci_read(TWL4030_BCICTL1, &bcictl1);
			if (ret < 0)
				return ret;
			val->intval = regval2ua(val->intval, bcictl1 &
							TWL4030_CGAIN);
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}