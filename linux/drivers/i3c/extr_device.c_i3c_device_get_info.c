#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i3c_device_info {int dummy; } ;
struct i3c_device {int /*<<< orphan*/  bus; TYPE_1__* desc; } ;
struct TYPE_2__ {struct i3c_device_info info; } ;

/* Variables and functions */
 int /*<<< orphan*/  i3c_bus_normaluse_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_unlock (int /*<<< orphan*/ ) ; 

void i3c_device_get_info(struct i3c_device *dev,
			 struct i3c_device_info *info)
{
	if (!info)
		return;

	i3c_bus_normaluse_lock(dev->bus);
	if (dev->desc)
		*info = dev->desc->info;
	i3c_bus_normaluse_unlock(dev->bus);
}