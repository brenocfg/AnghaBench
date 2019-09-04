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
typedef  size_t u8 ;
struct ib_gid_table {int dummy; } ;
struct TYPE_4__ {TYPE_3__* ports; } ;
struct ib_device {size_t phys_port_cnt; TYPE_1__ cache; TYPE_2__* port_immutable; } ;
struct TYPE_6__ {struct ib_gid_table* gid; } ;
struct TYPE_5__ {int /*<<< orphan*/  gid_tbl_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_gid_table* alloc_gid_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_table_release_one (struct ib_device*) ; 
 int /*<<< orphan*/  gid_table_reserve_default (struct ib_device*,size_t,struct ib_gid_table*) ; 
 size_t rdma_start_port (struct ib_device*) ; 

__attribute__((used)) static int _gid_table_setup_one(struct ib_device *ib_dev)
{
	u8 port;
	struct ib_gid_table *table;

	for (port = 0; port < ib_dev->phys_port_cnt; port++) {
		u8 rdma_port = port + rdma_start_port(ib_dev);

		table =	alloc_gid_table(
				ib_dev->port_immutable[rdma_port].gid_tbl_len);
		if (!table)
			goto rollback_table_setup;

		gid_table_reserve_default(ib_dev, rdma_port, table);
		ib_dev->cache.ports[port].gid = table;
	}
	return 0;

rollback_table_setup:
	gid_table_release_one(ib_dev);
	return -ENOMEM;
}