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
struct i3c_device {int /*<<< orphan*/  bus; TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ibi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  i3c_bus_normaluse_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_bus_normaluse_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_dev_free_ibi_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i3c_device_free_ibi(struct i3c_device *dev)
{
	i3c_bus_normaluse_lock(dev->bus);
	if (dev->desc) {
		mutex_lock(&dev->desc->ibi_lock);
		i3c_dev_free_ibi_locked(dev->desc);
		mutex_unlock(&dev->desc->ibi_lock);
	}
	i3c_bus_normaluse_unlock(dev->bus);
}