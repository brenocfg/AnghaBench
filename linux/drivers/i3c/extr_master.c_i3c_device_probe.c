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
struct i3c_driver {int (* probe ) (struct i3c_device*) ;} ;
struct i3c_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct i3c_device* dev_to_i3cdev (struct device*) ; 
 struct i3c_driver* drv_to_i3cdrv (int /*<<< orphan*/ ) ; 
 int stub1 (struct i3c_device*) ; 

__attribute__((used)) static int i3c_device_probe(struct device *dev)
{
	struct i3c_device *i3cdev = dev_to_i3cdev(dev);
	struct i3c_driver *driver = drv_to_i3cdrv(dev->driver);

	return driver->probe(i3cdev);
}