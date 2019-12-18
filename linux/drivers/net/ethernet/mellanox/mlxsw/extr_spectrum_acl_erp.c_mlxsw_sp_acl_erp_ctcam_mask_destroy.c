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
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  key; struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ctcam_dec (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_master_mask_clear (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_ctcam_disable (struct mlxsw_sp_acl_erp_table*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_ctcam_mask_destroy(struct mlxsw_sp_acl_erp *erp)
{
	struct mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;

	mlxsw_sp_acl_erp_region_ctcam_disable(erp_table);
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &erp->key);
	mlxsw_sp_acl_erp_ctcam_dec(erp_table);
	kfree(erp);
}