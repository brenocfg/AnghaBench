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
struct thermal_zone_device {struct mlxsw_thermal* devdata; } ;
struct mlxsw_thermal {TYPE_1__* trips; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLXSW_THERMAL_NUM_TRIPS ; 

__attribute__((used)) static int mlxsw_thermal_get_trip_type(struct thermal_zone_device *tzdev,
				       int trip,
				       enum thermal_trip_type *p_type)
{
	struct mlxsw_thermal *thermal = tzdev->devdata;

	if (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		return -EINVAL;

	*p_type = thermal->trips[trip].type;
	return 0;
}