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
union power_supply_propval {int intval; } ;
struct ucs1002_info {int /*<<< orphan*/  regmap; } ;
typedef  enum power_supply_usb_type { ____Placeholder_power_supply_usb_type } power_supply_usb_type ;

/* Variables and functions */
#define  F_ACTIVE_MODE_BC12_CDP 131 
#define  F_ACTIVE_MODE_BC12_DCP 130 
#define  F_ACTIVE_MODE_BC12_SDP 129 
#define  F_ACTIVE_MODE_DEDICATED 128 
 unsigned int F_ACTIVE_MODE_MASK ; 
 int POWER_SUPPLY_USB_TYPE_CDP ; 
 int POWER_SUPPLY_USB_TYPE_DCP ; 
 int POWER_SUPPLY_USB_TYPE_PD ; 
 int POWER_SUPPLY_USB_TYPE_SDP ; 
 int POWER_SUPPLY_USB_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  UCS1002_REG_PIN_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ucs1002_get_usb_type(struct ucs1002_info *info,
				union power_supply_propval *val)
{
	enum power_supply_usb_type type;
	unsigned int reg;
	int ret;

	ret = regmap_read(info->regmap, UCS1002_REG_PIN_STATUS, &reg);
	if (ret)
		return ret;

	switch (reg & F_ACTIVE_MODE_MASK) {
	default:
		type = POWER_SUPPLY_USB_TYPE_UNKNOWN;
		break;
	case F_ACTIVE_MODE_DEDICATED:
		type = POWER_SUPPLY_USB_TYPE_PD;
		break;
	case F_ACTIVE_MODE_BC12_SDP:
		type = POWER_SUPPLY_USB_TYPE_SDP;
		break;
	case F_ACTIVE_MODE_BC12_DCP:
		type = POWER_SUPPLY_USB_TYPE_DCP;
		break;
	case F_ACTIVE_MODE_BC12_CDP:
		type = POWER_SUPPLY_USB_TYPE_CDP;
		break;
	}

	val->intval = type;

	return 0;
}