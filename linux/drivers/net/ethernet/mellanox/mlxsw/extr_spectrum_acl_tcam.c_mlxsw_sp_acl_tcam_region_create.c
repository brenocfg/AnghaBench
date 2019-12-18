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
struct mlxsw_sp_acl_tcam_vregion {int /*<<< orphan*/  key_info; } ;
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; int /*<<< orphan*/  key_type; int /*<<< orphan*/  key_info; struct mlxsw_sp_acl_tcam_vregion* vregion; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_acl_tcam_ops {int (* region_associate ) (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ;int (* region_init ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_tcam_region*,void*) ;int /*<<< orphan*/  key_type; scalar_t__ region_priv_size; } ;
struct mlxsw_sp_acl_tcam {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_tcam_region* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_region*) ; 
 struct mlxsw_sp_acl_tcam_region* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_region_alloc (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_disable (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int mlxsw_sp_acl_tcam_region_enable (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_free (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int mlxsw_sp_acl_tcam_region_id_get (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_id_put (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int stub2 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_tcam_region*,void*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_region *
mlxsw_sp_acl_tcam_region_create(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam *tcam,
				struct mlxsw_sp_acl_tcam_vregion *vregion,
				void *hints_priv)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_sp_acl_tcam_region *region;
	int err;

	region = kzalloc(sizeof(*region) + ops->region_priv_size, GFP_KERNEL);
	if (!region)
		return ERR_PTR(-ENOMEM);
	region->mlxsw_sp = mlxsw_sp;
	region->vregion = vregion;
	region->key_info = vregion->key_info;

	err = mlxsw_sp_acl_tcam_region_id_get(tcam, &region->id);
	if (err)
		goto err_region_id_get;

	err = ops->region_associate(mlxsw_sp, region);
	if (err)
		goto err_tcam_region_associate;

	region->key_type = ops->key_type;
	err = mlxsw_sp_acl_tcam_region_alloc(mlxsw_sp, region);
	if (err)
		goto err_tcam_region_alloc;

	err = mlxsw_sp_acl_tcam_region_enable(mlxsw_sp, region);
	if (err)
		goto err_tcam_region_enable;

	err = ops->region_init(mlxsw_sp, region->priv, tcam->priv,
			       region, hints_priv);
	if (err)
		goto err_tcam_region_init;

	return region;

err_tcam_region_init:
	mlxsw_sp_acl_tcam_region_disable(mlxsw_sp, region);
err_tcam_region_enable:
	mlxsw_sp_acl_tcam_region_free(mlxsw_sp, region);
err_tcam_region_alloc:
err_tcam_region_associate:
	mlxsw_sp_acl_tcam_region_id_put(tcam, region->id);
err_region_id_get:
	kfree(region);
	return ERR_PTR(err);
}