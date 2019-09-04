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
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hsi_bus_match(struct device *dev, struct device_driver *driver)
{
	if (of_driver_match_device(dev, driver))
		return true;

	if (strcmp(dev_name(dev), driver->name) == 0)
		return true;

	return false;
}