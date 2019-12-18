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
struct ucs1002_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  POWER_SUPPLY_USB_TYPE_CDP 131 
#define  POWER_SUPPLY_USB_TYPE_DCP 130 
#define  POWER_SUPPLY_USB_TYPE_PD 129 
#define  POWER_SUPPLY_USB_TYPE_SDP 128 
 int /*<<< orphan*/  UCS1002_REG_SWITCH_CFG ; 
 unsigned int V_SET_ACTIVE_MODE_BC12_CDP ; 
 unsigned int V_SET_ACTIVE_MODE_BC12_DCP ; 
 unsigned int V_SET_ACTIVE_MODE_BC12_SDP ; 
 unsigned int V_SET_ACTIVE_MODE_DEDICATED ; 
 int /*<<< orphan*/  V_SET_ACTIVE_MODE_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int* ucs1002_usb_types ; 

__attribute__((used)) static int ucs1002_set_usb_type(struct ucs1002_info *info, int val)
{
	unsigned int mode;

	if (val < 0 || val >= ARRAY_SIZE(ucs1002_usb_types))
		return -EINVAL;

	switch (ucs1002_usb_types[val]) {
	case POWER_SUPPLY_USB_TYPE_PD:
		mode = V_SET_ACTIVE_MODE_DEDICATED;
		break;
	case POWER_SUPPLY_USB_TYPE_SDP:
		mode = V_SET_ACTIVE_MODE_BC12_SDP;
		break;
	case POWER_SUPPLY_USB_TYPE_DCP:
		mode = V_SET_ACTIVE_MODE_BC12_DCP;
		break;
	case POWER_SUPPLY_USB_TYPE_CDP:
		mode = V_SET_ACTIVE_MODE_BC12_CDP;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(info->regmap, UCS1002_REG_SWITCH_CFG,
				  V_SET_ACTIVE_MODE_MASK, mode);
}