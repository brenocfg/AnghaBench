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
struct iser_device {int /*<<< orphan*/  ig_list; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_list_mutex; } ;

/* Variables and functions */
 TYPE_1__ ig ; 
 int /*<<< orphan*/  iser_free_device_ib_res (struct iser_device*) ; 
 int /*<<< orphan*/  iser_info (char*,struct iser_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iser_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iser_device_try_release(struct iser_device *device)
{
	mutex_lock(&ig.device_list_mutex);
	device->refcount--;
	iser_info("device %p refcount %d\n", device, device->refcount);
	if (!device->refcount) {
		iser_free_device_ib_res(device);
		list_del(&device->ig_list);
		kfree(device);
	}
	mutex_unlock(&ig.device_list_mutex);
}