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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  key_info; int /*<<< orphan*/  id; int /*<<< orphan*/  priv; int /*<<< orphan*/  key_type; struct mlxsw_sp* mlxsw_sp; int /*<<< orphan*/  chunk_list; } ;
struct mlxsw_sp_acl_tcam_ops {int (* region_associate ) (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ;int (* region_init ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_tcam_region*) ;int /*<<< orphan*/  key_type; scalar_t__ region_priv_size; } ;
struct mlxsw_sp_acl_tcam {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp {int /*<<< orphan*/  acl; struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct mlxsw_afk_element_usage {int dummy; } ;
struct mlxsw_afk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_acl_tcam_region* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_region*) ; 
 struct mlxsw_sp_acl_tcam_region* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_get (struct mlxsw_afk*,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_afk_key_info_put (int /*<<< orphan*/ ) ; 
 struct mlxsw_afk* mlxsw_sp_acl_afk (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_region_alloc (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_disable (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int mlxsw_sp_acl_tcam_region_enable (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_free (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int mlxsw_sp_acl_tcam_region_id_get (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_id_put (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int stub2 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_tcam_region*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_region *
mlxsw_sp_acl_tcam_region_create(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_acl_tcam *tcam,
				struct mlxsw_afk_element_usage *elusage)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	struct mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	struct mlxsw_sp_acl_tcam_region *region;
	int err;

	region = kzalloc(sizeof(*region) + ops->region_priv_size, GFP_KERNEL);
	if (!region)
		return ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&region->chunk_list);
	region->mlxsw_sp = mlxsw_sp;

	region->key_info = mlxsw_afk_key_info_get(afk, elusage);
	if (IS_ERR(region->key_info)) {
		err = PTR_ERR(region->key_info);
		goto err_key_info_get;
	}

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

	err = ops->region_init(mlxsw_sp, region->priv, tcam->priv, region);
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
	mlxsw_afk_key_info_put(region->key_info);
err_key_info_get:
	kfree(region);
	return ERR_PTR(err);
}