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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {scalar_t__ ctcam; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  index; TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  erp_single_mask_ops ; 
 void mlxsw_sp_acl_erp_ctcam_mask_destroy (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_generic_destroy (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_index_put (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_erp_del (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_master_mask_trans (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_erp_del (struct mlxsw_sp_acl_erp*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_second_mask_destroy(struct mlxsw_sp_acl_erp_table *erp_table,
				     struct mlxsw_sp_acl_erp *erp)
{
	if (erp->key.ctcam)
		return mlxsw_sp_acl_erp_ctcam_mask_destroy(erp);

	mlxsw_sp_acl_erp_region_erp_del(erp);
	mlxsw_sp_acl_erp_table_erp_del(erp);
	mlxsw_sp_acl_erp_index_put(erp_table, erp->index);
	mlxsw_sp_acl_erp_generic_destroy(erp);
	/* Transition to use master mask instead of eRP table */
	mlxsw_sp_acl_erp_region_master_mask_trans(erp_table);

	erp_table->ops = &erp_single_mask_ops;
}