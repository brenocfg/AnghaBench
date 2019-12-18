#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct charger_manager {scalar_t__ tzd_batt; TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  measure_battery_temp; } ;

/* Variables and functions */
 int ENODEV ; 
 int cm_get_battery_temperature_by_psy (struct charger_manager*,int*) ; 
 int thermal_zone_get_temp (scalar_t__,int*) ; 

__attribute__((used)) static int cm_get_battery_temperature(struct charger_manager *cm,
					int *temp)
{
	int ret;

	if (!cm->desc->measure_battery_temp)
		return -ENODEV;

#ifdef CONFIG_THERMAL
	if (cm->tzd_batt) {
		ret = thermal_zone_get_temp(cm->tzd_batt, temp);
		if (!ret)
			/* Calibrate temperature unit */
			*temp /= 100;
	} else
#endif
	{
		/* if-else continued from CONFIG_THERMAL */
		ret = cm_get_battery_temperature_by_psy(cm, temp);
	}

	return ret;
}