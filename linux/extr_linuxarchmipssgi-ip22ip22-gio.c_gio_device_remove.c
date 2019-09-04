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
struct gio_driver {int /*<<< orphan*/  (* remove ) (struct gio_device*) ;} ;
struct gio_device {int dummy; } ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct gio_device*) ; 
 struct gio_device* to_gio_device (struct device*) ; 
 struct gio_driver* to_gio_driver (scalar_t__) ; 

__attribute__((used)) static int gio_device_remove(struct device *dev)
{
	struct gio_device *gio_dev = to_gio_device(dev);
	struct gio_driver *drv = to_gio_driver(dev->driver);

	if (dev->driver && drv->remove)
		drv->remove(gio_dev);
	return 0;
}