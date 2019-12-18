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
struct objagg_hints {int dummy; } ;
struct mlxsw_sp_acl_erp_table {int dummy; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_erp_table*) ; 
 int PTR_ERR (struct mlxsw_sp_acl_erp_table*) ; 
 int mlxsw_sp_acl_erp_master_mask_init (struct mlxsw_sp_acl_atcam_region*) ; 
 int mlxsw_sp_acl_erp_region_param_init (struct mlxsw_sp_acl_atcam_region*) ; 
 struct mlxsw_sp_acl_erp_table* mlxsw_sp_acl_erp_table_create (struct mlxsw_sp_acl_atcam_region*,struct objagg_hints*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_destroy (struct mlxsw_sp_acl_erp_table*) ; 

int mlxsw_sp_acl_erp_region_init(struct mlxsw_sp_acl_atcam_region *aregion,
				 void *hints_priv)
{
	struct mlxsw_sp_acl_erp_table *erp_table;
	struct objagg_hints *hints = hints_priv;
	int err;

	erp_table = mlxsw_sp_acl_erp_table_create(aregion, hints);
	if (IS_ERR(erp_table))
		return PTR_ERR(erp_table);
	aregion->erp_table = erp_table;

	/* Initialize the region's master mask to all zeroes */
	err = mlxsw_sp_acl_erp_master_mask_init(aregion);
	if (err)
		goto err_erp_master_mask_init;

	/* Initialize the region to not use the eRP table */
	err = mlxsw_sp_acl_erp_region_param_init(aregion);
	if (err)
		goto err_erp_region_param_init;

	return 0;

err_erp_region_param_init:
err_erp_master_mask_init:
	mlxsw_sp_acl_erp_table_destroy(erp_table);
	return err;
}