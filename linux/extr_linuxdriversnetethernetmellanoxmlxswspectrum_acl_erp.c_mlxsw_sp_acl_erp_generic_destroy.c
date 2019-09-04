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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  num_atcam_erps; int /*<<< orphan*/  erp_ht; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  id; int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_id_put (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_master_mask_clear (struct mlxsw_sp_acl_erp_table*,struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_generic_destroy(struct mlxsw_sp_acl_erp *erp)
{
	struct mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;

	rhashtable_remove_fast(&erp_table->erp_ht, &erp->ht_node,
			       mlxsw_sp_acl_erp_ht_params);
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, erp);
	erp_table->num_atcam_erps--;
	list_del(&erp->list);
	mlxsw_sp_acl_erp_id_put(erp_table, erp->id);
	kfree(erp);
}