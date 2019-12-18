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
struct mlxsw_sp_acl_tcam_vregion {int /*<<< orphan*/  lock; int /*<<< orphan*/  vchunk_list; int /*<<< orphan*/  region; } ;
struct mlxsw_sp_acl_tcam_vgroup {int /*<<< orphan*/  vchunk_ht; } ;
struct mlxsw_sp_acl_tcam_vchunk {unsigned int priority; int ref_count; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  list; struct mlxsw_sp_acl_tcam_vregion* chunk; struct mlxsw_sp_acl_tcam_vregion* vregion; struct mlxsw_sp_acl_tcam_vgroup* vgroup; int /*<<< orphan*/  ventry_list; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlxsw_sp_acl_tcam_vchunk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_tcam_vregion*) ; 
 unsigned int MLXSW_SP_ACL_TCAM_CATCHALL_PRIO ; 
 int PTR_ERR (struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_vchunk*) ; 
 struct mlxsw_sp_acl_tcam_vchunk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_acl_tcam_vregion* mlxsw_sp_acl_tcam_chunk_create (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vchunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed (struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vchunk_ht_params ; 
 struct mlxsw_sp_acl_tcam_vregion* mlxsw_sp_acl_tcam_vregion_get (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vgroup*,unsigned int,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vregion_put (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_vchunk *
mlxsw_sp_acl_tcam_vchunk_create(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam_vgroup *vgroup,
				unsigned int priority,
				struct mlxsw_afk_element_usage *elusage)
{
	struct mlxsw_sp_acl_tcam_vregion *vregion;
	struct mlxsw_sp_acl_tcam_vchunk *vchunk;
	int err;

	if (priority == MLXSW_SP_ACL_TCAM_CATCHALL_PRIO)
		return ERR_PTR(-EINVAL);

	vchunk = kzalloc(sizeof(*vchunk), GFP_KERNEL);
	if (!vchunk)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&vchunk->ventry_list);
	vchunk->priority = priority;
	vchunk->vgroup = vgroup;
	vchunk->ref_count = 1;

	vregion = mlxsw_sp_acl_tcam_vregion_get(mlxsw_sp, vgroup,
						priority, elusage);
	if (IS_ERR(vregion)) {
		err = PTR_ERR(vregion);
		goto err_vregion_get;
	}

	vchunk->vregion = vregion;

	err = rhashtable_insert_fast(&vgroup->vchunk_ht, &vchunk->ht_node,
				     mlxsw_sp_acl_tcam_vchunk_ht_params);
	if (err)
		goto err_rhashtable_insert;

	mutex_lock(&vregion->lock);
	vchunk->chunk = mlxsw_sp_acl_tcam_chunk_create(mlxsw_sp, vchunk,
						       vchunk->vregion->region);
	if (IS_ERR(vchunk->chunk)) {
		mutex_unlock(&vregion->lock);
		err = PTR_ERR(vchunk->chunk);
		goto err_chunk_create;
	}

	mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed(vregion);
	list_add_tail(&vchunk->list, &vregion->vchunk_list);
	mutex_unlock(&vregion->lock);

	return vchunk;

err_chunk_create:
	rhashtable_remove_fast(&vgroup->vchunk_ht, &vchunk->ht_node,
			       mlxsw_sp_acl_tcam_vchunk_ht_params);
err_rhashtable_insert:
	mlxsw_sp_acl_tcam_vregion_put(mlxsw_sp, vregion);
err_vregion_get:
	kfree(vchunk);
	return ERR_PTR(err);
}