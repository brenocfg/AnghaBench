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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ rmi_function_match (struct device*,struct device_driver*) ; 
 int rmi_is_physical_device (struct device*) ; 
 int rmi_is_physical_driver (struct device_driver*) ; 

__attribute__((used)) static int rmi_bus_match(struct device *dev, struct device_driver *drv)
{
	bool physical = rmi_is_physical_device(dev);

	/* First see if types are not compatible */
	if (physical != rmi_is_physical_driver(drv))
		return 0;

	return physical || rmi_function_match(dev, drv);
}