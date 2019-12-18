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
 int POWER_SUPPLY_CAPACITY_LEVEL_FULL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int hidpp_map_battery_level (int) ; 

__attribute__((used)) static int hidpp20_batterylevel_map_status_capacity(u8 data[3], int *capacity,
						    int *next_capacity,
						    int *level)
{
	int status;

	*capacity = data[0];
	*next_capacity = data[1];
	*level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;

	/* When discharging, we can rely on the device reported capacity.
	 * For all other states the device reports 0 (unknown).
	 */
	switch (data[2]) {
		case 0: /* discharging (in use) */
			status = POWER_SUPPLY_STATUS_DISCHARGING;
			*level = hidpp_map_battery_level(*capacity);
			break;
		case 1: /* recharging */
			status = POWER_SUPPLY_STATUS_CHARGING;
			break;
		case 2: /* charge in final stage */
			status = POWER_SUPPLY_STATUS_CHARGING;
			break;
		case 3: /* charge complete */
			status = POWER_SUPPLY_STATUS_FULL;
			*level = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
			*capacity = 100;
			break;
		case 4: /* recharging below optimal speed */
			status = POWER_SUPPLY_STATUS_CHARGING;
			break;
		/* 5 = invalid battery type
		   6 = thermal error
		   7 = other charging error */
		default:
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			break;
	}

	return status;
}