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
typedef  int u8 ;
typedef  int u16 ;
struct ib_device {TYPE_1__* port_immutable; } ;
struct TYPE_2__ {int gid_tbl_len; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  memcmp (union ib_gid*,union ib_gid*,int) ; 
 int rdma_end_port (struct ib_device*) ; 
 int /*<<< orphan*/  rdma_protocol_ib (struct ib_device*,int) ; 
 int rdma_query_gid (struct ib_device*,int,int,union ib_gid*) ; 
 int rdma_start_port (struct ib_device*) ; 

int ib_find_gid(struct ib_device *device, union ib_gid *gid,
		u8 *port_num, u16 *index)
{
	union ib_gid tmp_gid;
	int ret, port, i;

	for (port = rdma_start_port(device); port <= rdma_end_port(device); ++port) {
		if (!rdma_protocol_ib(device, port))
			continue;

		for (i = 0; i < device->port_immutable[port].gid_tbl_len; ++i) {
			ret = rdma_query_gid(device, port, i, &tmp_gid);
			if (ret)
				return ret;
			if (!memcmp(&tmp_gid, gid, sizeof *gid)) {
				*port_num = port;
				if (index)
					*index = i;
				return 0;
			}
		}
	}

	return -ENOENT;
}