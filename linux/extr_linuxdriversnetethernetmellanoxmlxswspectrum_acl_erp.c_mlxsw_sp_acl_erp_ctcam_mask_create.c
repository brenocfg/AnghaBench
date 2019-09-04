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
struct mlxsw_sp_acl_erp_table {int dummy; } ;
struct mlxsw_sp_acl_erp_key {int dummy; } ;
struct mlxsw_sp_acl_erp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_acl_erp* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_erp*) ; 
 int PTR_ERR (struct mlxsw_sp_acl_erp*) ; 
 struct mlxsw_sp_acl_erp* __mlxsw_sp_acl_erp_ctcam_mask_create (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp_key*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_master_mask_trans (struct mlxsw_sp_acl_erp_table*) ; 
 int mlxsw_sp_acl_erp_region_table_trans (struct mlxsw_sp_acl_erp_table*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_ctcam_mask_create(struct mlxsw_sp_acl_erp_table *erp_table,
				   struct mlxsw_sp_acl_erp_key *key)
{
	struct mlxsw_sp_acl_erp *erp;
	int err;

	/* There is a special situation where we need to spill rules
	 * into the C-TCAM, yet the region is still using a master
	 * mask and thus not performing a lookup in the C-TCAM. This
	 * can happen when two rules that only differ in priority - and
	 * thus sharing the same key - are programmed. In this case
	 * we transition the region to use an eRP table
	 */
	err = mlxsw_sp_acl_erp_region_table_trans(erp_table);
	if (err)
		return ERR_PTR(err);

	erp = __mlxsw_sp_acl_erp_ctcam_mask_create(erp_table, key);
	if (IS_ERR(erp)) {
		err = PTR_ERR(erp);
		goto err_erp_create;
	}

	return erp;

err_erp_create:
	mlxsw_sp_acl_erp_region_master_mask_trans(erp_table);
	return ERR_PTR(err);
}