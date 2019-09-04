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
typedef  union ib_gid {int dummy; } ib_gid ;
struct sockaddr {int dummy; } ;
struct rdma_addr {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct TYPE_2__ {struct rdma_addr addr; } ;
struct rdma_cm_id {int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; TYPE_1__ route; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union ib_gid*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_addr_get_dgid (int /*<<< orphan*/ *,union ib_gid*) ; 
 int /*<<< orphan*/  rdma_addr_get_sgid (int /*<<< orphan*/ *,union ib_gid*) ; 
 int /*<<< orphan*/  rdma_ip2gid (struct sockaddr*,union ib_gid*) ; 
 scalar_t__ rdma_protocol_roce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rdma_read_gids(struct rdma_cm_id *cm_id, union ib_gid *sgid,
		    union ib_gid *dgid)
{
	struct rdma_addr *addr = &cm_id->route.addr;

	if (!cm_id->device) {
		if (sgid)
			memset(sgid, 0, sizeof(*sgid));
		if (dgid)
			memset(dgid, 0, sizeof(*dgid));
		return;
	}

	if (rdma_protocol_roce(cm_id->device, cm_id->port_num)) {
		if (sgid)
			rdma_ip2gid((struct sockaddr *)&addr->src_addr, sgid);
		if (dgid)
			rdma_ip2gid((struct sockaddr *)&addr->dst_addr, dgid);
	} else {
		if (sgid)
			rdma_addr_get_sgid(&addr->dev_addr, sgid);
		if (dgid)
			rdma_addr_get_dgid(&addr->dev_addr, dgid);
	}
}