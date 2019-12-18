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
typedef  int /*<<< orphan*/  u32 ;
struct ib_device {int /*<<< orphan*/  compat_devs_mutex; int /*<<< orphan*/  compat_devs; } ;
struct ib_core_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_free_port_attrs (struct ib_core_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct ib_core_device* xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_one_compat_dev(struct ib_device *device, u32 id)
{
	struct ib_core_device *cdev;

	mutex_lock(&device->compat_devs_mutex);
	cdev = xa_erase(&device->compat_devs, id);
	mutex_unlock(&device->compat_devs_mutex);
	if (cdev) {
		ib_free_port_attrs(cdev);
		device_del(&cdev->dev);
		put_device(&cdev->dev);
	}
}