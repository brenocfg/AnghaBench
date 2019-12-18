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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/ * ops; } ;
struct mlxsw_sp_acl_erp_key {scalar_t__ ctcam; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_erp* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  erp_multiple_masks_ops ; 
 struct mlxsw_sp_acl_erp* mlxsw_sp_acl_erp_ctcam_mask_create (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp_key*) ; 
 struct mlxsw_sp_acl_erp* mlxsw_sp_acl_erp_generic_create (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp_key*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_generic_destroy (struct mlxsw_sp_acl_erp*) ; 
 int mlxsw_sp_acl_erp_index_get (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_index_put (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_erp_region_erp_add (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int mlxsw_sp_acl_erp_table_erp_add (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_erp_del (struct mlxsw_sp_acl_erp*) ; 
 int mlxsw_sp_acl_erp_table_expand (struct mlxsw_sp_acl_erp_table*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_mask_create(struct mlxsw_sp_acl_erp_table *erp_table,
			     struct mlxsw_sp_acl_erp_key *key)
{
	struct mlxsw_sp_acl_erp *erp;
	int err;

	if (key->ctcam)
		return mlxsw_sp_acl_erp_ctcam_mask_create(erp_table, key);

	/* Expand the eRP table for the new eRP, if needed */
	err = mlxsw_sp_acl_erp_table_expand(erp_table);
	if (err)
		return ERR_PTR(err);

	erp = mlxsw_sp_acl_erp_generic_create(erp_table, key);
	if (IS_ERR(erp))
		return erp;

	err = mlxsw_sp_acl_erp_index_get(erp_table, &erp->index);
	if (err)
		goto err_erp_index_get;

	err = mlxsw_sp_acl_erp_table_erp_add(erp_table, erp);
	if (err)
		goto err_table_erp_add;

	err = mlxsw_sp_acl_erp_region_erp_add(erp_table, erp);
	if (err)
		goto err_region_erp_add;

	erp_table->ops = &erp_multiple_masks_ops;

	return erp;

err_region_erp_add:
	mlxsw_sp_acl_erp_table_erp_del(erp);
err_table_erp_add:
	mlxsw_sp_acl_erp_index_put(erp_table, erp->index);
err_erp_index_get:
	mlxsw_sp_acl_erp_generic_destroy(erp);
	return ERR_PTR(err);
}