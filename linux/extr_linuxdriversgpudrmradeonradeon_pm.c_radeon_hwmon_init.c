#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int int_thermal_type; int /*<<< orphan*/  int_hwmon_dev; } ;
struct radeon_device {int /*<<< orphan*/  dev; TYPE_3__ pm; TYPE_2__* asic; } ;
struct TYPE_4__ {int /*<<< orphan*/ * get_temperature; } ;
struct TYPE_5__ {TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  THERMAL_TYPE_CI 135 
#define  THERMAL_TYPE_EVERGREEN 134 
#define  THERMAL_TYPE_KV 133 
#define  THERMAL_TYPE_NI 132 
#define  THERMAL_TYPE_RV6XX 131 
#define  THERMAL_TYPE_RV770 130 
#define  THERMAL_TYPE_SI 129 
#define  THERMAL_TYPE_SUMO 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hwmon_device_register_with_groups (int /*<<< orphan*/ ,char*,struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_groups ; 

__attribute__((used)) static int radeon_hwmon_init(struct radeon_device *rdev)
{
	int err = 0;

	switch (rdev->pm.int_thermal_type) {
	case THERMAL_TYPE_RV6XX:
	case THERMAL_TYPE_RV770:
	case THERMAL_TYPE_EVERGREEN:
	case THERMAL_TYPE_NI:
	case THERMAL_TYPE_SUMO:
	case THERMAL_TYPE_SI:
	case THERMAL_TYPE_CI:
	case THERMAL_TYPE_KV:
		if (rdev->asic->pm.get_temperature == NULL)
			return err;
		rdev->pm.int_hwmon_dev = hwmon_device_register_with_groups(rdev->dev,
									   "radeon", rdev,
									   hwmon_groups);
		if (IS_ERR(rdev->pm.int_hwmon_dev)) {
			err = PTR_ERR(rdev->pm.int_hwmon_dev);
			dev_err(rdev->dev,
				"Unable to register hwmon device: %d\n", err);
		}
		break;
	default:
		break;
	}

	return err;
}