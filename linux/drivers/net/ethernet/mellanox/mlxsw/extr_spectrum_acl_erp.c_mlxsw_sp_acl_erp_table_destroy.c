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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  objagg; int /*<<< orphan*/  objagg_lock; int /*<<< orphan*/  atcam_erps_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_erp_table*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objagg_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_table_destroy(struct mlxsw_sp_acl_erp_table *erp_table)
{
	WARN_ON(!list_empty(&erp_table->atcam_erps_list));
	mutex_destroy(&erp_table->objagg_lock);
	objagg_destroy(erp_table->objagg);
	kfree(erp_table);
}