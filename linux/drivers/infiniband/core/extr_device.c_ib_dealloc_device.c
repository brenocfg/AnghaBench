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
struct TYPE_2__ {int /*<<< orphan*/  (* dealloc_driver ) (struct ib_device*) ;} ;
struct ib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  refcount; int /*<<< orphan*/  client_data; int /*<<< orphan*/  compat_devs; int /*<<< orphan*/  index; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  devices_rwsem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdevs (struct ib_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_restrack_clean (struct ib_device*) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_device* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ib_dealloc_device(struct ib_device *device)
{
	if (device->ops.dealloc_driver)
		device->ops.dealloc_driver(device);

	/*
	 * ib_unregister_driver() requires all devices to remain in the xarray
	 * while their ops are callable. The last op we call is dealloc_driver
	 * above.  This is needed to create a fence on op callbacks prior to
	 * allowing the driver module to unload.
	 */
	down_write(&devices_rwsem);
	if (xa_load(&devices, device->index) == device)
		xa_erase(&devices, device->index);
	up_write(&devices_rwsem);

	/* Expedite releasing netdev references */
	free_netdevs(device);

	WARN_ON(!xa_empty(&device->compat_devs));
	WARN_ON(!xa_empty(&device->client_data));
	WARN_ON(refcount_read(&device->refcount));
	rdma_restrack_clean(device);
	/* Balances with device_initialize */
	put_device(&device->dev);
}