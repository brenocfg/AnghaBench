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
struct power_supply_battery_ocv_table {int dummy; } ;
struct power_supply_battery_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct power_supply_battery_ocv_table* power_supply_find_ocv2cap_table (struct power_supply_battery_info*,int,int*) ; 
 int power_supply_ocv2cap_simple (struct power_supply_battery_ocv_table*,int,int) ; 

int power_supply_batinfo_ocv2cap(struct power_supply_battery_info *info,
				 int ocv, int temp)
{
	struct power_supply_battery_ocv_table *table;
	int table_len;

	table = power_supply_find_ocv2cap_table(info, temp, &table_len);
	if (!table)
		return -EINVAL;

	return power_supply_ocv2cap_simple(table, table_len, ocv);
}