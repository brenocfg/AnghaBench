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
struct device {int dummy; } ;

/* Variables and functions */
 struct device* __hwmon_device_register (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

struct device *hwmon_device_register(struct device *dev)
{
	dev_warn(dev,
		 "hwmon_device_register() is deprecated. Please convert the driver to use hwmon_device_register_with_info().\n");

	return __hwmon_device_register(dev, NULL, NULL, NULL, NULL);
}