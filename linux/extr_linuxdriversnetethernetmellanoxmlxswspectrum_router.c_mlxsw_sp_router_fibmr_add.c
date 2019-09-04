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
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_mr_table {int dummy; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_4__ {int /*<<< orphan*/  family; } ;
struct mfc_entry_notifier_info {int /*<<< orphan*/  mfc; TYPE_2__ info; int /*<<< orphan*/  tb_id; } ;
struct TYPE_3__ {scalar_t__ aborted; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_vr*) ; 
 int PTR_ERR (struct mlxsw_sp_vr*) ; 
 int mlxsw_sp_mr_route_add (struct mlxsw_sp_mr_table*,int /*<<< orphan*/ ,int) ; 
 struct mlxsw_sp_mr_table* mlxsw_sp_router_fibmr_family_to_table (struct mlxsw_sp_vr*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_router_fibmr_add(struct mlxsw_sp *mlxsw_sp,
				     struct mfc_entry_notifier_info *men_info,
				     bool replace)
{
	struct mlxsw_sp_mr_table *mrt;
	struct mlxsw_sp_vr *vr;

	if (mlxsw_sp->router->aborted)
		return 0;

	vr = mlxsw_sp_vr_get(mlxsw_sp, men_info->tb_id, NULL);
	if (IS_ERR(vr))
		return PTR_ERR(vr);

	mrt = mlxsw_sp_router_fibmr_family_to_table(vr, men_info->info.family);
	return mlxsw_sp_mr_route_add(mrt, men_info->mfc, replace);
}