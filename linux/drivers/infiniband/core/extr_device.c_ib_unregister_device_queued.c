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
struct TYPE_2__ {int /*<<< orphan*/  dealloc_driver; } ;
struct ib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  unregistration_work; TYPE_1__ ops; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

void ib_unregister_device_queued(struct ib_device *ib_dev)
{
	WARN_ON(!refcount_read(&ib_dev->refcount));
	WARN_ON(!ib_dev->ops.dealloc_driver);
	get_device(&ib_dev->dev);
	if (!queue_work(system_unbound_wq, &ib_dev->unregistration_work))
		put_device(&ib_dev->dev);
}