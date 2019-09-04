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
struct TYPE_3__ {TYPE_2__* ports; } ;
struct ib_device {TYPE_1__ cache; } ;
struct TYPE_4__ {struct TYPE_4__* pkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  gid_table_release_one (struct ib_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int rdma_end_port (struct ib_device*) ; 
 int rdma_start_port (struct ib_device*) ; 

void ib_cache_release_one(struct ib_device *device)
{
	int p;

	/*
	 * The release function frees all the cache elements.
	 * This function should be called as part of freeing
	 * all the device's resources when the cache could no
	 * longer be accessed.
	 */
	for (p = 0; p <= rdma_end_port(device) - rdma_start_port(device); ++p)
		kfree(device->cache.ports[p].pkey);

	gid_table_release_one(device);
	kfree(device->cache.ports);
}