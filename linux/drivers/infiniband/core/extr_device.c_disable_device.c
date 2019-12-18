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
typedef  scalar_t__ u32 ;
struct ib_device {int /*<<< orphan*/  unreg_completion; int /*<<< orphan*/  index; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_REGISTERED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clients_rwsem ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  devices_rwsem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ highest_client_id ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_client_context (struct ib_device*,scalar_t__) ; 
 int /*<<< orphan*/  remove_compat_devs (struct ib_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_clear_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_device(struct ib_device *device)
{
	u32 cid;

	WARN_ON(!refcount_read(&device->refcount));

	down_write(&devices_rwsem);
	xa_clear_mark(&devices, device->index, DEVICE_REGISTERED);
	up_write(&devices_rwsem);

	/*
	 * Remove clients in LIFO order, see assign_client_id. This could be
	 * more efficient if xarray learns to reverse iterate. Since no new
	 * clients can be added to this ib_device past this point we only need
	 * the maximum possible client_id value here.
	 */
	down_read(&clients_rwsem);
	cid = highest_client_id;
	up_read(&clients_rwsem);
	while (cid) {
		cid--;
		remove_client_context(device, cid);
	}

	/* Pairs with refcount_set in enable_device */
	ib_device_put(device);
	wait_for_completion(&device->unreg_completion);

	/*
	 * compat devices must be removed after device refcount drops to zero.
	 * Otherwise init_net() may add more compatdevs after removing compat
	 * devices and before device is disabled.
	 */
	remove_compat_devs(device);
}