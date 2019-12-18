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
struct mlxsw_thermal_module {TYPE_1__* trips; int /*<<< orphan*/  module; } ;
struct mlxsw_core {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int temp; } ;

/* Variables and functions */
 int MLXSW_THERMAL_MODULE_TEMP_SHIFT ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_CRIT ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_HIGH ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_HOT ; 
 size_t MLXSW_THERMAL_TEMP_TRIP_NORM ; 
 int /*<<< orphan*/  SFP_TEMP_HIGH_ALARM ; 
 int /*<<< orphan*/  SFP_TEMP_HIGH_WARN ; 
 int mlxsw_env_module_temp_thresholds_get (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mlxsw_thermal_module_trips_update(struct device *dev, struct mlxsw_core *core,
				  struct mlxsw_thermal_module *tz)
{
	int crit_temp, emerg_temp;
	int err;

	err = mlxsw_env_module_temp_thresholds_get(core, tz->module,
						   SFP_TEMP_HIGH_WARN,
						   &crit_temp);
	if (err)
		return err;

	err = mlxsw_env_module_temp_thresholds_get(core, tz->module,
						   SFP_TEMP_HIGH_ALARM,
						   &emerg_temp);
	if (err)
		return err;

	/* According to the system thermal requirements, the thermal zones are
	 * defined with four trip points. The critical and emergency
	 * temperature thresholds, provided by QSFP module are set as "active"
	 * and "hot" trip points, "normal" and "critical" trip points are
	 * derived from "active" and "hot" by subtracting or adding double
	 * hysteresis value.
	 */
	if (crit_temp >= MLXSW_THERMAL_MODULE_TEMP_SHIFT)
		tz->trips[MLXSW_THERMAL_TEMP_TRIP_NORM].temp = crit_temp -
					MLXSW_THERMAL_MODULE_TEMP_SHIFT;
	else
		tz->trips[MLXSW_THERMAL_TEMP_TRIP_NORM].temp = crit_temp;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HIGH].temp = crit_temp;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HOT].temp = emerg_temp;
	if (emerg_temp > crit_temp)
		tz->trips[MLXSW_THERMAL_TEMP_TRIP_CRIT].temp = emerg_temp +
					MLXSW_THERMAL_MODULE_TEMP_SHIFT;
	else
		tz->trips[MLXSW_THERMAL_TEMP_TRIP_CRIT].temp = emerg_temp;

	return 0;
}