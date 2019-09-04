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
struct mlxsw_sp_nexthop {int /*<<< orphan*/  ht_node; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  nexthop_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_nexthop_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_nexthop_remove(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_nexthop *nh)
{
	rhashtable_remove_fast(&mlxsw_sp->router->nexthop_ht, &nh->ht_node,
			       mlxsw_sp_nexthop_ht_params);
}