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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  num_atcam_erps; } ;
struct mlxsw_sp_acl_erp {int /*<<< orphan*/  id; int /*<<< orphan*/  list; int /*<<< orphan*/  key; struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_id_put (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_master_mask_clear (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_generic_destroy(struct mlxsw_sp_acl_erp *erp)
{
	struct mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;

	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &erp->key);
	erp_table->num_atcam_erps--;
	list_del(&erp->list);
	mlxsw_sp_acl_erp_id_put(erp_table, erp->id);
	kfree(erp);
}