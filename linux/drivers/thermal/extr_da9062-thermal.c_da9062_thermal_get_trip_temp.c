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
struct thermal_zone_device {struct da9062_thermal* devdata; } ;
struct da9062_thermal {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DA9062_MILLI_CELSIUS (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int da9062_thermal_get_trip_temp(struct thermal_zone_device *z,
					int trip,
					int *temp)
{
	struct da9062_thermal *thermal = z->devdata;

	switch (trip) {
	case 0:
		*temp = DA9062_MILLI_CELSIUS(125);
		break;
	default:
		dev_err(thermal->dev,
			"Driver does not support more than 1 trip-wire\n");
		return -EINVAL;
	}

	return 0;
}