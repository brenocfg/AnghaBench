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
struct xpc_partition_uv {int flags; } ;
struct TYPE_3__ {struct xpc_partition_uv uv; } ;
struct TYPE_4__ {TYPE_1__ sn; } ;

/* Variables and functions */
 int XPC_P_ENGAGED_UV ; 
 short XP_MAX_NPARTITIONS_UV ; 
 TYPE_2__* xpc_partitions ; 

__attribute__((used)) static int
xpc_any_partition_engaged_uv(void)
{
	struct xpc_partition_uv *part_uv;
	short partid;

	for (partid = 0; partid < XP_MAX_NPARTITIONS_UV; partid++) {
		part_uv = &xpc_partitions[partid].sn.uv;
		if ((part_uv->flags & XPC_P_ENGAGED_UV) != 0)
			return 1;
	}
	return 0;
}