#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct devcd_entry {TYPE_2__* failing_dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ sd; } ;
struct TYPE_4__ {TYPE_1__ kobj; } ;

/* Variables and functions */
 struct devcd_entry* dev_to_devcd (struct device*) ; 
 int /*<<< orphan*/  kfree (struct devcd_entry*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_delete_link (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void devcd_dev_release(struct device *dev)
{
	struct devcd_entry *devcd = dev_to_devcd(dev);

	devcd->free(devcd->data);
	module_put(devcd->owner);

	/*
	 * this seems racy, but I don't see a notifier or such on
	 * a struct device to know when it goes away?
	 */
	if (devcd->failing_dev->kobj.sd)
		sysfs_delete_link(&devcd->failing_dev->kobj, &dev->kobj,
				  "devcoredump");

	put_device(devcd->failing_dev);
	kfree(devcd);
}