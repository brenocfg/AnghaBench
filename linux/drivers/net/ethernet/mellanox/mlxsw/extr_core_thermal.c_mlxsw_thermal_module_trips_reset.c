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
struct mlxsw_thermal_module {TYPE_1__* trips; } ;
struct TYPE_2__ {scalar_t__ temp; } ;

/* Variables and functions */
 size_t MLXSW_THERMAL_TEMP_TRIP_CRIT ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_HIGH ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_HOT ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_NORM ; 

__attribute__((used)) static void
mlxsw_thermal_module_trips_reset(struct mlxsw_thermal_module *tz)
{
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_NORM].temp = 0;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HIGH].temp = 0;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HOT].temp = 0;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_CRIT].temp = 0;
}