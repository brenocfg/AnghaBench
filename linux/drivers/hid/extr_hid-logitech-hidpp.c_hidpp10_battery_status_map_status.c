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
typedef  int u8 ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 

__attribute__((used)) static int hidpp10_battery_status_map_status(u8 param)
{
	int status;

	switch (param) {
	case 0x00:
		/* discharging (in use) */
		status = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case 0x21: /* (standard) charging */
	case 0x24: /* fast charging */
	case 0x25: /* slow charging */
		status = POWER_SUPPLY_STATUS_CHARGING;
		break;
	case 0x26: /* topping charge */
	case 0x22: /* charge complete */
		status = POWER_SUPPLY_STATUS_FULL;
		break;
	case 0x20: /* unknown */
		status = POWER_SUPPLY_STATUS_UNKNOWN;
		break;
	/*
	 * 0x01...0x1F = reserved (not charging)
	 * 0x23 = charging error
	 * 0x27..0xff = reserved
	 */
	default:
		status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	}

	return status;
}