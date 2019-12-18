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
struct TYPE_2__ {int /*<<< orphan*/  dw; } ;
struct mlxsw_sp_acl_tcam_vregion {int /*<<< orphan*/  lock; int /*<<< orphan*/  key_info; scalar_t__ region; scalar_t__ region2; TYPE_1__ rehash; int /*<<< orphan*/  tlist; struct mlxsw_sp_acl_tcam* tcam; struct mlxsw_sp_acl_tcam_vgroup* vgroup; } ;
struct mlxsw_sp_acl_tcam_vgroup {scalar_t__ vregion_rehash_enabled; } ;
struct mlxsw_sp_acl_tcam_ops {scalar_t__ region_rehash_hints_get; } ;
struct mlxsw_sp_acl_tcam {int /*<<< orphan*/  lock; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_destroy (struct mlxsw_sp*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vgroup_vregion_detach (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_vregion_destroy(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_acl_tcam_vregion *vregion)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_vgroup *vgroup = vregion->vgroup;
	struct mlxsw_sp_acl_tcam *tcam = vregion->tcam;

	if (vgroup->vregion_rehash_enabled && ops->region_rehash_hints_get) {
		mutex_lock(&tcam->lock);
		list_del(&vregion->tlist);
		mutex_unlock(&tcam->lock);
		cancel_delayed_work_sync(&vregion->rehash.dw);
	}
	mlxsw_sp_acl_tcam_vgroup_vregion_detach(mlxsw_sp, vregion);
	if (vregion->region2)
		mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, vregion->region2);
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, vregion->region);
	mlxsw_afk_key_info_put(vregion->key_info);
	mutex_destroy(&vregion->lock);
	kfree(vregion);
}