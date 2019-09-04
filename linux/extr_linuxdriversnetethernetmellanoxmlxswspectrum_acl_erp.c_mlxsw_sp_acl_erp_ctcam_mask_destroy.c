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
struct mlxsw_sp_acl_erp_table {scalar_t__ num_ctcam_erps; int /*<<< orphan*/  erp_ht; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  ht_node; struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ctcam_table_ops_set (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_master_mask_clear (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_ctcam_disable (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_ctcam_mask_destroy(struct mlxsw_sp_acl_erp *erp)
{
	struct mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;

	mlxsw_sp_acl_erp_region_ctcam_disable(erp_table);
	rhashtable_remove_fast(&erp_table->erp_ht, &erp->ht_node,
			       mlxsw_sp_acl_erp_ht_params);
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, erp);
	erp_table->num_ctcam_erps--;
	kfree(erp);

	/* Once the last C-TCAM eRP was destroyed, the state we
	 * transition to depends on the number of A-TCAM eRPs currently
	 * in use
	 */
	if (erp_table->num_ctcam_erps > 0)
		return;
	mlxsw_sp_acl_erp_ctcam_table_ops_set(erp_table);
}