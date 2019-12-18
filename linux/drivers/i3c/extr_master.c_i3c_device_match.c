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
struct i3c_driver {int /*<<< orphan*/  id_table; } ;
struct i3c_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 struct i3c_device* dev_to_i3cdev (struct device*) ; 
 struct i3c_driver* drv_to_i3cdrv (struct device_driver*) ; 
 scalar_t__ i3c_device_match_id (struct i3c_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_device_type ; 

__attribute__((used)) static int i3c_device_match(struct device *dev, struct device_driver *drv)
{
	struct i3c_device *i3cdev;
	struct i3c_driver *i3cdrv;

	if (dev->type != &i3c_device_type)
		return 0;

	i3cdev = dev_to_i3cdev(dev);
	i3cdrv = drv_to_i3cdrv(drv);
	if (i3c_device_match_id(i3cdev, i3cdrv->id_table))
		return 1;

	return 0;
}