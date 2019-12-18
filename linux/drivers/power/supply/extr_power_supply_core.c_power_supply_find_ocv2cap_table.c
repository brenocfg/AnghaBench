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
typedef  size_t u8 ;
struct power_supply_battery_ocv_table {int dummy; } ;
struct power_supply_battery_info {int* ocv_table_size; struct power_supply_battery_ocv_table** ocv_table; scalar_t__* ocv_temp; } ;

/* Variables and functions */
 int INT_MAX ; 
 size_t POWER_SUPPLY_OCV_TEMP_MAX ; 
 int abs (scalar_t__) ; 

struct power_supply_battery_ocv_table *
power_supply_find_ocv2cap_table(struct power_supply_battery_info *info,
				int temp, int *table_len)
{
	int best_temp_diff = INT_MAX, temp_diff;
	u8 i, best_index = 0;

	if (!info->ocv_table[0])
		return NULL;

	for (i = 0; i < POWER_SUPPLY_OCV_TEMP_MAX; i++) {
		temp_diff = abs(info->ocv_temp[i] - temp);

		if (temp_diff < best_temp_diff) {
			best_temp_diff = temp_diff;
			best_index = i;
		}
	}

	*table_len = info->ocv_table_size[best_index];
	return info->ocv_table[best_index];
}