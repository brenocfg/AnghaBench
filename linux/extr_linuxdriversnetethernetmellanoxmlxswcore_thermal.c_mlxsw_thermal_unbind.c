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
struct mlxsw_thermal {TYPE_1__* bus_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int MLXSW_THERMAL_NUM_TRIPS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ mlxsw_get_cooling_device_idx (struct mlxsw_thermal*,struct thermal_cooling_device*) ; 
 int thermal_zone_unbind_cooling_device (struct thermal_zone_device*,int,struct thermal_cooling_device*) ; 

__attribute__((used)) static int mlxsw_thermal_unbind(struct thermal_zone_device *tzdev,
				struct thermal_cooling_device *cdev)
{
	struct mlxsw_thermal *thermal = tzdev->devdata;
	struct device *dev = thermal->bus_info->dev;
	int i;
	int err;

	/* If the cooling device is our one unbind it */
	if (mlxsw_get_cooling_device_idx(thermal, cdev) < 0)
		return 0;

	for (i = 0; i < MLXSW_THERMAL_NUM_TRIPS; i++) {
		err = thermal_zone_unbind_cooling_device(tzdev, i, cdev);
		if (err < 0) {
			dev_err(dev, "Failed to unbind cooling device\n");
			return err;
		}
	}
	return 0;
}