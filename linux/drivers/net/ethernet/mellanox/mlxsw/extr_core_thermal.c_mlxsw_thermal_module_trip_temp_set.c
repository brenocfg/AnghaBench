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
struct thermal_zone_device {struct mlxsw_thermal_module* devdata; } ;
struct mlxsw_thermal_module {TYPE_1__* trips; } ;
struct TYPE_2__ {int temp; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLXSW_THERMAL_NUM_TRIPS ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_CRIT ; 

__attribute__((used)) static int
mlxsw_thermal_module_trip_temp_set(struct thermal_zone_device *tzdev,
				   int trip, int temp)
{
	struct mlxsw_thermal_module *tz = tzdev->devdata;

	if (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS ||
	    temp > tz->trips[MLXSW_THERMAL_TEMP_TRIP_CRIT].temp)
		return -EINVAL;

	tz->trips[trip].temp = temp;
	return 0;
}