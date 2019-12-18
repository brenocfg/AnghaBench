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
struct thermal_zone_device {struct mlxsw_thermal_module* devdata; } ;
struct mlxsw_thermal_module {struct mlxsw_thermal* parent; } ;
struct mlxsw_thermal {struct thermal_zone_device* tz_highest_dev; } ;
typedef  enum thermal_trend { ____Placeholder_thermal_trend } thermal_trend ;

/* Variables and functions */
 int EINVAL ; 
 int MLXSW_THERMAL_NUM_TRIPS ; 
 int THERMAL_TREND_STABLE ; 

__attribute__((used)) static int mlxsw_thermal_trend_get(struct thermal_zone_device *tzdev,
				   int trip, enum thermal_trend *trend)
{
	struct mlxsw_thermal_module *tz = tzdev->devdata;
	struct mlxsw_thermal *thermal = tz->parent;

	if (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		return -EINVAL;

	if (tzdev == thermal->tz_highest_dev)
		return 1;

	*trend = THERMAL_TREND_STABLE;
	return 0;
}