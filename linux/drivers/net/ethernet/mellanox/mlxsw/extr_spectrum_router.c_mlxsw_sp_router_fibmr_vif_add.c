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
struct vif_entry_notifier_info {int /*<<< orphan*/  vif_flags; int /*<<< orphan*/  vif_index; int /*<<< orphan*/  dev; TYPE_2__ info; int /*<<< orphan*/  tb_id; } ;
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_mr_table {int dummy; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_3__ {scalar_t__ aborted; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_vr*) ; 
 int PTR_ERR (struct mlxsw_sp_vr*) ; 
 int mlxsw_sp_mr_vif_add (struct mlxsw_sp_mr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_rif*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_mr_table* mlxsw_sp_router_fibmr_family_to_table (struct mlxsw_sp_vr*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_router_fibmr_vif_add(struct mlxsw_sp *mlxsw_sp,
			      struct vif_entry_notifier_info *ven_info)
{
	struct mlxsw_sp_mr_table *mrt;
	struct mlxsw_sp_rif *rif;
	struct mlxsw_sp_vr *vr;

	if (mlxsw_sp->router->aborted)
		return 0;

	vr = mlxsw_sp_vr_get(mlxsw_sp, ven_info->tb_id, NULL);
	if (IS_ERR(vr))
		return PTR_ERR(vr);

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, ven_info->info.family);
	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, ven_info->dev);
	return mlxsw_sp_mr_vif_add(mrt, ven_info->dev,
				   ven_info->vif_index,
				   ven_info->vif_flags, rif);
}