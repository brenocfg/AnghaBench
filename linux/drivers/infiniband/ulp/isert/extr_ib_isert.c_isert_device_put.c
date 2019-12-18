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
struct isert_device {int /*<<< orphan*/  dev_node; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_list_mutex ; 
 int /*<<< orphan*/  isert_free_device_ib_res (struct isert_device*) ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct isert_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_device_put(struct isert_device *device)
{
	mutex_lock(&device_list_mutex);
	device->refcount--;
	isert_info("device %p refcount %d\n", device, device->refcount);
	if (!device->refcount) {
		isert_free_device_ib_res(device);
		list_del(&device->dev_node);
		kfree(device);
	}
	mutex_unlock(&device_list_mutex);
}