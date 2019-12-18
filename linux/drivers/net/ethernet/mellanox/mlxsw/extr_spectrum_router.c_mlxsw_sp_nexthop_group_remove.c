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
struct mlxsw_sp_nexthop_group {int /*<<< orphan*/  ht_node; int /*<<< orphan*/  gateway; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  nexthop_group_ht; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_group_ht_params ; 
 scalar_t__ mlxsw_sp_nexthop_group_type (struct mlxsw_sp_nexthop_group*) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_nexthop_group_remove(struct mlxsw_sp *mlxsw_sp,
					  struct mlxsw_sp_nexthop_group *nh_grp)
{
	if (mlxsw_sp_nexthop_group_type(nh_grp) == AF_INET6 &&
	    !nh_grp->gateway)
		return;

	rhashtable_remove_fast(&mlxsw_sp->router->nexthop_group_ht,
			       &nh_grp->ht_node,
			       mlxsw_sp_nexthop_group_ht_params);
}