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
struct ib_uverbs_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  comp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  devnum; int /*<<< orphan*/  cdev; } ;
struct TYPE_2__ {scalar_t__ disassociate_ucontext; } ;
struct ib_device {TYPE_1__ ops; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_uverbs_comp_dev (struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  ib_uverbs_free_hw_resources (struct ib_uverbs_device*,struct ib_device*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_ida ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_uverbs_remove_one(struct ib_device *device, void *client_data)
{
	struct ib_uverbs_device *uverbs_dev = client_data;
	int wait_clients = 1;

	if (!uverbs_dev)
		return;

	cdev_device_del(&uverbs_dev->cdev, &uverbs_dev->dev);
	ida_free(&uverbs_ida, uverbs_dev->devnum);

	if (device->ops.disassociate_ucontext) {
		/* We disassociate HW resources and immediately return.
		 * Userspace will see a EIO errno for all future access.
		 * Upon returning, ib_device may be freed internally and is not
		 * valid any more.
		 * uverbs_device is still available until all clients close
		 * their files, then the uverbs device ref count will be zero
		 * and its resources will be freed.
		 * Note: At this point no more files can be opened since the
		 * cdev was deleted, however active clients can still issue
		 * commands and close their open files.
		 */
		ib_uverbs_free_hw_resources(uverbs_dev, device);
		wait_clients = 0;
	}

	if (atomic_dec_and_test(&uverbs_dev->refcount))
		ib_uverbs_comp_dev(uverbs_dev);
	if (wait_clients)
		wait_for_completion(&uverbs_dev->comp);

	put_device(&uverbs_dev->dev);
}