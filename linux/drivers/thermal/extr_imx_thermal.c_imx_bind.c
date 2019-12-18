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
struct thermal_zone_device {int /*<<< orphan*/  type; int /*<<< orphan*/  device; } ;
struct thermal_cooling_device {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_TRIP_PASSIVE ; 
 int /*<<< orphan*/  THERMAL_NO_LIMIT ; 
 int /*<<< orphan*/  THERMAL_WEIGHT_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int thermal_zone_bind_cooling_device (struct thermal_zone_device*,int /*<<< orphan*/ ,struct thermal_cooling_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_bind(struct thermal_zone_device *tz,
		    struct thermal_cooling_device *cdev)
{
	int ret;

	ret = thermal_zone_bind_cooling_device(tz, IMX_TRIP_PASSIVE, cdev,
					       THERMAL_NO_LIMIT,
					       THERMAL_NO_LIMIT,
					       THERMAL_WEIGHT_DEFAULT);
	if (ret) {
		dev_err(&tz->device,
			"binding zone %s with cdev %s failed:%d\n",
			tz->type, cdev->type, ret);
		return ret;
	}

	return 0;
}