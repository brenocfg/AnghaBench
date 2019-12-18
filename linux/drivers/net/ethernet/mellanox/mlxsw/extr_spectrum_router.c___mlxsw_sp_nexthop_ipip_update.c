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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_nexthop {TYPE_2__* ipip_entry; } ;
struct mlxsw_sp_ipip_ops {int (* nexthop_update ) (struct mlxsw_sp*,int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_4__ {size_t ipipt; } ;
struct TYPE_3__ {struct mlxsw_sp_ipip_ops** ipip_ops_arr; } ;

/* Variables and functions */
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int __mlxsw_sp_nexthop_ipip_update(struct mlxsw_sp *mlxsw_sp,
					  u32 adj_index,
					  struct mlxsw_sp_nexthop *nh)
{
	const struct mlxsw_sp_ipip_ops *ipip_ops;

	ipip_ops = mlxsw_sp->router->ipip_ops_arr[nh->ipip_entry->ipipt];
	return ipip_ops->nexthop_update(mlxsw_sp, adj_index, nh->ipip_entry);
}