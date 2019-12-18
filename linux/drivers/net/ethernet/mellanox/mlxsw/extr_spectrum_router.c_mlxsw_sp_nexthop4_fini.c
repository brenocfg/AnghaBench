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
struct mlxsw_sp_nexthop {int /*<<< orphan*/  router_list_node; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop4_type_fini (struct mlxsw_sp*,struct mlxsw_sp_nexthop*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_counter_free (struct mlxsw_sp*,struct mlxsw_sp_nexthop*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_remove (struct mlxsw_sp*,struct mlxsw_sp_nexthop*) ; 

__attribute__((used)) static void mlxsw_sp_nexthop4_fini(struct mlxsw_sp *mlxsw_sp,
				   struct mlxsw_sp_nexthop *nh)
{
	mlxsw_sp_nexthop4_type_fini(mlxsw_sp, nh);
	list_del(&nh->router_list_node);
	mlxsw_sp_nexthop_counter_free(mlxsw_sp, nh);
	mlxsw_sp_nexthop_remove(mlxsw_sp, nh);
}