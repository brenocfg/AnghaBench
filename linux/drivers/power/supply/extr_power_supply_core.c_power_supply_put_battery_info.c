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
struct power_supply_battery_info {scalar_t__* ocv_table; } ;
struct power_supply {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int POWER_SUPPLY_OCV_TEMP_MAX ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,scalar_t__) ; 

void power_supply_put_battery_info(struct power_supply *psy,
				   struct power_supply_battery_info *info)
{
	int i;

	for (i = 0; i < POWER_SUPPLY_OCV_TEMP_MAX; i++) {
		if (info->ocv_table[i])
			devm_kfree(&psy->dev, info->ocv_table[i]);
	}
}