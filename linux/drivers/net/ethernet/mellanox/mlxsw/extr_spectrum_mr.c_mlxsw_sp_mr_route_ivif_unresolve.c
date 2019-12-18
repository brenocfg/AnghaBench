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
struct mlxsw_sp_mr_table {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_mr_route_vif_entry {TYPE_2__* mr_route; } ;
struct mlxsw_sp_mr {TYPE_1__* mr_ops; } ;
struct mlxsw_sp {struct mlxsw_sp_mr* mr; } ;
struct TYPE_4__ {int /*<<< orphan*/  route_action; int /*<<< orphan*/  route_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* route_action_update ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_MR_ROUTE_ACTION_TRAP ; 
 int /*<<< orphan*/  mlxsw_sp_mr_mfc_offload_update (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_mr_route_ivif_unresolve(struct mlxsw_sp_mr_table *mr_table,
				 struct mlxsw_sp_mr_route_vif_entry *rve)
{
	struct mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	struct mlxsw_sp_mr *mr = mlxsw_sp->mr;

	mr->mr_ops->route_action_update(mlxsw_sp, rve->mr_route->route_priv,
					MLXSW_SP_MR_ROUTE_ACTION_TRAP);
	rve->mr_route->route_action = MLXSW_SP_MR_ROUTE_ACTION_TRAP;
	mlxsw_sp_mr_mfc_offload_update(rve->mr_route);
}