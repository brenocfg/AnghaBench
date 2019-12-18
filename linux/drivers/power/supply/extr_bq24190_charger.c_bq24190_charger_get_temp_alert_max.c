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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int bq24190_battery_get_temp_alert_max (struct bq24190_dev_info*,union power_supply_propval*) ; 

__attribute__((used)) static int bq24190_charger_get_temp_alert_max(struct bq24190_dev_info *bdi,
					      union power_supply_propval *val)
{
	return bq24190_battery_get_temp_alert_max(bdi, val);
}