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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  num_deltas; } ;

/* Variables and functions */
 int __mlxsw_sp_acl_erp_table_other_inc (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_acl_erp_delta_inc(struct mlxsw_sp_acl_erp_table *erp_table)
{
	return __mlxsw_sp_acl_erp_table_other_inc(erp_table,
						  &erp_table->num_deltas);
}