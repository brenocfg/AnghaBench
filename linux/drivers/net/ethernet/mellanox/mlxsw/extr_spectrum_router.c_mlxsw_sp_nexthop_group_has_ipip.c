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
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; } ;
struct mlxsw_sp_nexthop {scalar_t__ type; struct mlxsw_sp_nexthop_group* nh_grp; } ;

/* Variables and functions */
 scalar_t__ MLXSW_SP_NEXTHOP_TYPE_IPIP ; 

bool mlxsw_sp_nexthop_group_has_ipip(struct mlxsw_sp_nexthop *nh)
{
	struct mlxsw_sp_nexthop_group *nh_grp = nh->nh_grp;
	int i;

	for (i = 0; i < nh_grp->count; i++) {
		struct mlxsw_sp_nexthop *nh_iter = &nh_grp->nexthops[i];

		if (nh_iter->type == MLXSW_SP_NEXTHOP_TYPE_IPIP)
			return true;
	}
	return false;
}