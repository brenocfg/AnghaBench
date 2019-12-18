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
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcoe_bus_type ; 

__attribute__((used)) static int fcoe_bus_match(struct device *dev,
			  struct device_driver *drv)
{
	if (dev->bus == &fcoe_bus_type)
		return 1;
	return 0;
}