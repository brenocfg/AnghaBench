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
struct TYPE_4__ {int /*<<< orphan*/  dw; } ;
struct mlxsw_sp_acl_tcam_vregion {int ref_count; int /*<<< orphan*/  key_info; int /*<<< orphan*/  region; int /*<<< orphan*/  tlist; TYPE_2__ rehash; struct mlxsw_sp_acl_tcam_vgroup* vgroup; struct mlxsw_sp* mlxsw_sp; struct mlxsw_sp_acl_tcam* tcam; int /*<<< orphan*/  lock; int /*<<< orphan*/  vchunk_list; } ;
struct TYPE_3__ {struct mlxsw_sp_acl_tcam* tcam; } ;
struct mlxsw_sp_acl_tcam_vgroup {scalar_t__ vregion_rehash_enabled; TYPE_1__ group; } ;
struct mlxsw_sp_acl_tcam_ops {scalar_t__ region_rehash_hints_get; } ;
struct mlxsw_sp_acl_tcam {int /*<<< orphan*/  lock; int /*<<< orphan*/  vregion_list; } ;
struct mlxsw_sp {int /*<<< orphan*/  acl; struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct mlxsw_afk_element_usage {int dummy; } ;
struct mlxsw_afk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_tcam_vregion* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_vregion*) ; 
 struct mlxsw_sp_acl_tcam_vregion* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_get (struct mlxsw_afk*,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_put (int /*<<< orphan*/ ) ; 
 struct mlxsw_afk* mlxsw_sp_acl_afk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_create (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam*,struct mlxsw_sp_acl_tcam_vregion*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_destroy (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_vgroup_vregion_attach (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vgroup*,struct mlxsw_sp_acl_tcam_vregion*,unsigned int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vregion_rehash_work ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vregion_rehash_work_schedule (struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_vregion *
mlxsw_sp_acl_tcam_vregion_create(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_tcam_vgroup *vgroup,
				 unsigned int priority,
				 struct mlxsw_afk_element_usage *elusage)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	struct mlxsw_sp_acl_tcam *tcam = vgroup->group.tcam;
	struct mlxsw_sp_acl_tcam_vregion *vregion;
	int err;

	vregion = kzalloc(sizeof(*vregion), GFP_KERNEL);
	if (!vregion)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&vregion->vchunk_list);
	mutex_init(&vregion->lock);
	vregion->tcam = tcam;
	vregion->mlxsw_sp = mlxsw_sp;
	vregion->vgroup = vgroup;
	vregion->ref_count = 1;

	vregion->key_info = mlxsw_afk_key_info_get(afk, elusage);
	if (IS_ERR(vregion->key_info)) {
		err = PTR_ERR(vregion->key_info);
		goto err_key_info_get;
	}

	vregion->region = mlxsw_sp_acl_tcam_region_create(mlxsw_sp, tcam,
							  vregion, NULL);
	if (IS_ERR(vregion->region)) {
		err = PTR_ERR(vregion->region);
		goto err_region_create;
	}

	err = mlxsw_sp_acl_tcam_vgroup_vregion_attach(mlxsw_sp, vgroup, vregion,
						      priority);
	if (err)
		goto err_vgroup_vregion_attach;

	if (vgroup->vregion_rehash_enabled && ops->region_rehash_hints_get) {
		/* Create the delayed work for vregion periodic rehash */
		INIT_DELAYED_WORK(&vregion->rehash.dw,
				  mlxsw_sp_acl_tcam_vregion_rehash_work);
		mlxsw_sp_acl_tcam_vregion_rehash_work_schedule(vregion);
		mutex_lock(&tcam->lock);
		list_add_tail(&vregion->tlist, &tcam->vregion_list);
		mutex_unlock(&tcam->lock);
	}

	return vregion;

err_vgroup_vregion_attach:
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, vregion->region);
err_region_create:
	mlxsw_afk_key_info_put(vregion->key_info);
err_key_info_get:
	kfree(vregion);
	return ERR_PTR(err);
}