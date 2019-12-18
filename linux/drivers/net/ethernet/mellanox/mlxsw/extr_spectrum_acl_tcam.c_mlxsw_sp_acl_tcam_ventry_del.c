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
struct mlxsw_sp_acl_tcam_vregion {int /*<<< orphan*/  lock; } ;
struct mlxsw_sp_acl_tcam_ventry {int /*<<< orphan*/  entry; int /*<<< orphan*/  list; struct mlxsw_sp_acl_tcam_vchunk* vchunk; } ;
struct mlxsw_sp_acl_tcam_vchunk {struct mlxsw_sp_acl_tcam_vregion* vregion; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_entry_destroy (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_rehash_ctx_vchunk_changed (struct mlxsw_sp_acl_tcam_vchunk*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vchunk_put (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vchunk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_acl_tcam_ventry_del(struct mlxsw_sp *mlxsw_sp,
					 struct mlxsw_sp_acl_tcam_ventry *ventry)
{
	struct mlxsw_sp_acl_tcam_vchunk *vchunk = ventry->vchunk;
	struct mlxsw_sp_acl_tcam_vregion *vregion = vchunk->vregion;

	mutex_lock(&vregion->lock);
	mlxsw_sp_acl_tcam_rehash_ctx_vchunk_changed(vchunk);
	list_del(&ventry->list);
	mlxsw_sp_acl_tcam_entry_destroy(mlxsw_sp, ventry->entry);
	mutex_unlock(&vregion->lock);
	mlxsw_sp_acl_tcam_vchunk_put(mlxsw_sp, vchunk);
}