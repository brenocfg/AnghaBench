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
struct mlxsw_sp_acl_tcam_region {int dummy; } ;
struct mlxsw_sp_acl_ctcam_region_ops {int dummy; } ;
struct mlxsw_sp_acl_atcam_region {int /*<<< orphan*/  entries_ht; TYPE_1__* ops; int /*<<< orphan*/  cregion; int /*<<< orphan*/  entries_list; struct mlxsw_sp_acl_atcam* atcam; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp_acl_atcam {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int (* init ) (struct mlxsw_sp_acl_atcam_region*) ;int /*<<< orphan*/  (* fini ) (struct mlxsw_sp_acl_atcam_region*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_entries_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_region_type_init (struct mlxsw_sp_acl_atcam_region*) ; 
 int mlxsw_sp_acl_ctcam_region_init (struct mlxsw_sp*,int /*<<< orphan*/ *,struct mlxsw_sp_acl_tcam_region*,struct mlxsw_sp_acl_ctcam_region_ops const*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_fini (struct mlxsw_sp_acl_atcam_region*) ; 
 int mlxsw_sp_acl_erp_region_init (struct mlxsw_sp_acl_atcam_region*,void*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (struct mlxsw_sp_acl_atcam_region*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_acl_atcam_region*) ; 

int
mlxsw_sp_acl_atcam_region_init(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_atcam *atcam,
			       struct mlxsw_sp_acl_atcam_region *aregion,
			       struct mlxsw_sp_acl_tcam_region *region,
			       void *hints_priv,
			       const struct mlxsw_sp_acl_ctcam_region_ops *ops)
{
	int err;

	aregion->region = region;
	aregion->atcam = atcam;
	mlxsw_sp_acl_atcam_region_type_init(aregion);
	INIT_LIST_HEAD(&aregion->entries_list);

	err = rhashtable_init(&aregion->entries_ht,
			      &mlxsw_sp_acl_atcam_entries_ht_params);
	if (err)
		return err;
	err = aregion->ops->init(aregion);
	if (err)
		goto err_ops_init;
	err = mlxsw_sp_acl_erp_region_init(aregion, hints_priv);
	if (err)
		goto err_erp_region_init;
	err = mlxsw_sp_acl_ctcam_region_init(mlxsw_sp, &aregion->cregion,
					     region, ops);
	if (err)
		goto err_ctcam_region_init;

	return 0;

err_ctcam_region_init:
	mlxsw_sp_acl_erp_region_fini(aregion);
err_erp_region_init:
	aregion->ops->fini(aregion);
err_ops_init:
	rhashtable_destroy(&aregion->entries_ht);
	return err;
}