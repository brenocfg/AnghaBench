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
struct thermal_cooling_device {int dummy; } ;
struct mlxsw_thermal_trip {int /*<<< orphan*/  min_state; int /*<<< orphan*/  max_state; } ;
struct mlxsw_thermal {struct mlxsw_thermal_trip* trips; TYPE_1__* bus_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int MLXSW_THERMAL_NUM_TRIPS ; 
 int /*<<< orphan*/  THERMAL_WEIGHT_DEFAULT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ mlxsw_get_cooling_device_idx (struct mlxsw_thermal*,struct thermal_cooling_device*) ; 
 int thermal_zone_bind_cooling_device (struct thermal_zone_device*,int,struct thermal_cooling_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_thermal_bind(struct thermal_zone_device *tzdev,
			      struct thermal_cooling_device *cdev)
{
	struct mlxsw_thermal *thermal = tzdev->devdata;
	struct device *dev = thermal->bus_info->dev;
	int i, err;

	/* If the cooling device is one of ours bind it */
	if (mlxsw_get_cooling_device_idx(thermal, cdev) < 0)
		return 0;

	for (i = 0; i < MLXSW_THERMAL_NUM_TRIPS; i++) {
		const struct mlxsw_thermal_trip *trip = &thermal->trips[i];

		err = thermal_zone_bind_cooling_device(tzdev, i, cdev,
						       trip->max_state,
						       trip->min_state,
						       THERMAL_WEIGHT_DEFAULT);
		if (err < 0) {
			dev_err(dev, "Failed to bind cooling device to trip %d\n", i);
			return err;
		}
	}
	return 0;
}