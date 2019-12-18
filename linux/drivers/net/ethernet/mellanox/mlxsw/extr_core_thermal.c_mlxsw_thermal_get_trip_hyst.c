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
struct TYPE_2__ {int hyst; } ;

/* Variables and functions */

__attribute__((used)) static int mlxsw_thermal_get_trip_hyst(struct thermal_zone_device *tzdev,
				       int trip, int *p_hyst)
{
	struct mlxsw_thermal *thermal = tzdev->devdata;

	*p_hyst = thermal->trips[trip].hyst;
	return 0;
}