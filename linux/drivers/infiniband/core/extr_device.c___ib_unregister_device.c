#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kref; } ;
struct TYPE_6__ {TYPE_1__ kobj; } ;
struct TYPE_5__ {scalar_t__ dealloc_driver; } ;
struct ib_device {int /*<<< orphan*/  unregistration_lock; TYPE_3__ dev; TYPE_2__ ops; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  device_del (TYPE_3__*) ; 
 int /*<<< orphan*/  disable_device (struct ib_device*) ; 
 int /*<<< orphan*/  free_netdevs (struct ib_device*) ; 
 int /*<<< orphan*/  ib_cache_cleanup_one (struct ib_device*) ; 
 int /*<<< orphan*/  ib_dealloc_device (struct ib_device*) ; 
 int /*<<< orphan*/  ib_device_unregister_rdmacg (struct ib_device*) ; 
 int /*<<< orphan*/  ib_device_unregister_sysfs (struct ib_device*) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ib_unregister_device(struct ib_device *ib_dev)
{
	/*
	 * We have a registration lock so that all the calls to unregister are
	 * fully fenced, once any unregister returns the device is truely
	 * unregistered even if multiple callers are unregistering it at the
	 * same time. This also interacts with the registration flow and
	 * provides sane semantics if register and unregister are racing.
	 */
	mutex_lock(&ib_dev->unregistration_lock);
	if (!refcount_read(&ib_dev->refcount))
		goto out;

	disable_device(ib_dev);

	/* Expedite removing unregistered pointers from the hash table */
	free_netdevs(ib_dev);

	ib_device_unregister_sysfs(ib_dev);
	device_del(&ib_dev->dev);
	ib_device_unregister_rdmacg(ib_dev);
	ib_cache_cleanup_one(ib_dev);

	/*
	 * Drivers using the new flow may not call ib_dealloc_device except
	 * in error unwind prior to registration success.
	 */
	if (ib_dev->ops.dealloc_driver) {
		WARN_ON(kref_read(&ib_dev->dev.kobj.kref) <= 1);
		ib_dealloc_device(ib_dev);
	}
out:
	mutex_unlock(&ib_dev->unregistration_lock);
}