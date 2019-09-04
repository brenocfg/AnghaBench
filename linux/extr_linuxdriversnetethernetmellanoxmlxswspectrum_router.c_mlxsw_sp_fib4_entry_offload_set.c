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
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; } ;
struct TYPE_4__ {TYPE_1__* fib_nh; } ;
struct mlxsw_sp_nexthop {TYPE_2__ key; scalar_t__ offloaded; } ;
struct mlxsw_sp_fib_entry {scalar_t__ type; struct mlxsw_sp_nexthop_group* nh_group; } ;
struct TYPE_3__ {int /*<<< orphan*/  nh_flags; } ;

/* Variables and functions */
 scalar_t__ MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP ; 
 scalar_t__ MLXSW_SP_FIB_ENTRY_TYPE_LOCAL ; 
 int /*<<< orphan*/  RTNH_F_OFFLOAD ; 

__attribute__((used)) static void
mlxsw_sp_fib4_entry_offload_set(struct mlxsw_sp_fib_entry *fib_entry)
{
	struct mlxsw_sp_nexthop_group *nh_grp = fib_entry->nh_group;
	int i;

	if (fib_entry->type == MLXSW_SP_FIB_ENTRY_TYPE_LOCAL ||
	    fib_entry->type == MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP) {
		nh_grp->nexthops->key.fib_nh->nh_flags |= RTNH_F_OFFLOAD;
		return;
	}

	for (i = 0; i < nh_grp->count; i++) {
		struct mlxsw_sp_nexthop *nh = &nh_grp->nexthops[i];

		if (nh->offloaded)
			nh->key.fib_nh->nh_flags |= RTNH_F_OFFLOAD;
		else
			nh->key.fib_nh->nh_flags &= ~RTNH_F_OFFLOAD;
	}
}