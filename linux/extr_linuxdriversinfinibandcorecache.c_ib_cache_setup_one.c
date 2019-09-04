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
struct TYPE_2__ {int /*<<< orphan*/  event_handler; int /*<<< orphan*/ * ports; int /*<<< orphan*/  lock; } ;
struct ib_device {TYPE_1__ cache; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int gid_table_setup_one (struct ib_device*) ; 
 int /*<<< orphan*/  ib_cache_event ; 
 int /*<<< orphan*/  ib_cache_update (struct ib_device*,int,int) ; 
 int /*<<< orphan*/  ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int rdma_end_port (struct ib_device*) ; 
 int rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

int ib_cache_setup_one(struct ib_device *device)
{
	int p;
	int err;

	rwlock_init(&device->cache.lock);

	device->cache.ports =
		kcalloc(rdma_end_port(device) - rdma_start_port(device) + 1,
			sizeof(*device->cache.ports),
			GFP_KERNEL);
	if (!device->cache.ports)
		return -ENOMEM;

	err = gid_table_setup_one(device);
	if (err) {
		kfree(device->cache.ports);
		device->cache.ports = NULL;
		return err;
	}

	for (p = 0; p <= rdma_end_port(device) - rdma_start_port(device); ++p)
		ib_cache_update(device, p + rdma_start_port(device), true);

	INIT_IB_EVENT_HANDLER(&device->cache.event_handler,
			      device, ib_cache_event);
	ib_register_event_handler(&device->cache.event_handler);
	return 0;
}