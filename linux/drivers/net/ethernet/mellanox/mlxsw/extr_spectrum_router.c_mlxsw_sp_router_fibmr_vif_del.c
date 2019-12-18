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
struct TYPE_4__ {int /*<<< orphan*/  family; } ;
struct vif_entry_notifier_info {int /*<<< orphan*/  vif_index; TYPE_2__ info; int /*<<< orphan*/  tb_id; } ;
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_mr_table {int dummy; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_3__ {scalar_t__ aborted; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_vif_del (struct mlxsw_sp_mr_table*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_mr_table* mlxsw_sp_router_fibmr_family_to_table (struct mlxsw_sp_vr*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_find (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_put (struct mlxsw_sp*,struct mlxsw_sp_vr*) ; 

__attribute__((used)) static void
mlxsw_sp_router_fibmr_vif_del(struct mlxsw_sp *mlxsw_sp,
			      struct vif_entry_notifier_info *ven_info)
{
	struct mlxsw_sp_mr_table *mrt;
	struct mlxsw_sp_vr *vr;

	if (mlxsw_sp->router->aborted)
		return;

	vr = mlxsw_sp_vr_find(mlxsw_sp, ven_info->tb_id);
	if (WARN_ON(!vr))
		return;

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, ven_info->info.family);
	mlxsw_sp_mr_vif_del(mrt, ven_info->vif_index);
	mlxsw_sp_vr_put(mlxsw_sp, vr);
}