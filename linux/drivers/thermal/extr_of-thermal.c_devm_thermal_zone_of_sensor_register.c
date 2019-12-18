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
struct thermal_zone_of_device_ops {int dummy; } ;
struct thermal_zone_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct thermal_zone_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  devm_thermal_zone_of_sensor_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct thermal_zone_device**) ; 
 struct thermal_zone_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct thermal_zone_device**) ; 
 struct thermal_zone_device* thermal_zone_of_sensor_register (struct device*,int,void*,struct thermal_zone_of_device_ops const*) ; 

struct thermal_zone_device *devm_thermal_zone_of_sensor_register(
	struct device *dev, int sensor_id,
	void *data, const struct thermal_zone_of_device_ops *ops)
{
	struct thermal_zone_device **ptr, *tzd;

	ptr = devres_alloc(devm_thermal_zone_of_sensor_release, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	tzd = thermal_zone_of_sensor_register(dev, sensor_id, data, ops);
	if (IS_ERR(tzd)) {
		devres_free(ptr);
		return tzd;
	}

	*ptr = tzd;
	devres_add(dev, ptr);

	return tzd;
}