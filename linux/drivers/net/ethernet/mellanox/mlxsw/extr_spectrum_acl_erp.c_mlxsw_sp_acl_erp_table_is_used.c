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

/* Variables and functions */
 int /*<<< orphan*/  erp_no_mask_ops ; 
 int /*<<< orphan*/  erp_single_mask_ops ; 

__attribute__((used)) static bool
mlxsw_sp_acl_erp_table_is_used(const struct mlxsw_sp_acl_erp_table *erp_table)
{
	return erp_table->ops != &erp_single_mask_ops &&
	       erp_table->ops != &erp_no_mask_ops;
}