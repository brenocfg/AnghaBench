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
struct mlxsw_sp_fid_ops {int /*<<< orphan*/  (* vni_clear ) (struct mlxsw_sp_fid*) ;} ;
struct mlxsw_sp_fid_family {struct mlxsw_sp* mlxsw_sp; struct mlxsw_sp_fid_ops* ops; } ;
struct mlxsw_sp_fid {int vni_valid; int /*<<< orphan*/  vni_ht_node; struct mlxsw_sp_fid_family* fid_family; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
struct TYPE_2__ {int /*<<< orphan*/  vni_ht; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_vni_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_fid*) ; 

void mlxsw_sp_fid_vni_clear(struct mlxsw_sp_fid *fid)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;
	const struct mlxsw_sp_fid_ops *ops = fid_family->ops;
	struct mlxsw_sp *mlxsw_sp = fid_family->mlxsw_sp;

	if (WARN_ON(!ops->vni_clear || !fid->vni_valid))
		return;

	fid->vni_valid = false;
	ops->vni_clear(fid);
	rhashtable_remove_fast(&mlxsw_sp->fid_core->vni_ht, &fid->vni_ht_node,
			       mlxsw_sp_fid_vni_ht_params);
}