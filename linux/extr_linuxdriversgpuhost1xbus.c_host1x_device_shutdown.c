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
struct host1x_driver {int /*<<< orphan*/  (* shutdown ) (struct host1x_device*) ;} ;
struct host1x_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct host1x_device*) ; 
 struct host1x_device* to_host1x_device (struct device*) ; 
 struct host1x_driver* to_host1x_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void host1x_device_shutdown(struct device *dev)
{
	struct host1x_driver *driver = to_host1x_driver(dev->driver);
	struct host1x_device *device = to_host1x_device(dev);

	if (driver->shutdown)
		driver->shutdown(device);
}