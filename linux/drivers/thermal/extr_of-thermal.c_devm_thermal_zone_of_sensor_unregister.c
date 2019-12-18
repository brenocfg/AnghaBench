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
struct thermal_zone_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_match ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_release ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thermal_zone_device*) ; 

void devm_thermal_zone_of_sensor_unregister(struct device *dev,
					    struct thermal_zone_device *tzd)
{
	WARN_ON(devres_release(dev, devm_thermal_zone_of_sensor_release,
			       devm_thermal_zone_of_sensor_match, tzd));
}