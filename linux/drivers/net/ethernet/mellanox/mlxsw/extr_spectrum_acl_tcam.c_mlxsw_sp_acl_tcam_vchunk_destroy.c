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
struct mlxsw_sp_acl_tcam_vgroup {int /*<<< orphan*/  vchunk_ht; } ;
struct mlxsw_sp_acl_tcam_vchunk {struct mlxsw_sp_acl_tcam_vregion* vregion; int /*<<< orphan*/  ht_node; scalar_t__ chunk; scalar_t__ chunk2; int /*<<< orphan*/  list; struct mlxsw_sp_acl_tcam_vgroup* vgroup; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_vchunk*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_destroy (struct mlxsw_sp*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed (struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vchunk_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vregion_put (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_vchunk_destroy(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_tcam_vchunk *vchunk)
{
	struct mlxsw_sp_acl_tcam_vregion *vregion = vchunk->vregion;
	struct mlxsw_sp_acl_tcam_vgroup *vgroup = vchunk->vgroup;

	mutex_lock(&vregion->lock);
	mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed(vregion);
	list_del(&vchunk->list);
	if (vchunk->chunk2)
		mlxsw_sp_acl_tcam_chunk_destroy(mlxsw_sp, vchunk->chunk2);
	mlxsw_sp_acl_tcam_chunk_destroy(mlxsw_sp, vchunk->chunk);
	mutex_unlock(&vregion->lock);
	rhashtable_remove_fast(&vgroup->vchunk_ht, &vchunk->ht_node,
			       mlxsw_sp_acl_tcam_vchunk_ht_params);
	mlxsw_sp_acl_tcam_vregion_put(mlxsw_sp, vchunk->vregion);
	kfree(vchunk);
}