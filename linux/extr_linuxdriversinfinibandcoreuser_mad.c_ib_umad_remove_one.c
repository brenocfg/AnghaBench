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
struct ib_umad_device {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * port; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umad_kill_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_cap_ib_mad (struct ib_device*,int) ; 
 int rdma_end_port (struct ib_device*) ; 
 int rdma_start_port (struct ib_device*) ; 

__attribute__((used)) static void ib_umad_remove_one(struct ib_device *device, void *client_data)
{
	struct ib_umad_device *umad_dev = client_data;
	int i;

	if (!umad_dev)
		return;

	for (i = 0; i <= rdma_end_port(device) - rdma_start_port(device); ++i) {
		if (rdma_cap_ib_mad(device, i + rdma_start_port(device)))
			ib_umad_kill_port(&umad_dev->port[i]);
	}

	kobject_put(&umad_dev->kobj);
}