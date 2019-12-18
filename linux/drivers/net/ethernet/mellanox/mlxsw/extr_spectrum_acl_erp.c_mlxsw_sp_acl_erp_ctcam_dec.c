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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  num_ctcam_erps; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_acl_erp_table_other_dec (struct mlxsw_sp_acl_erp_table*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_acl_erp_ctcam_dec(struct mlxsw_sp_acl_erp_table *erp_table)
{
	__mlxsw_sp_acl_erp_table_other_dec(erp_table,
					   &erp_table->num_ctcam_erps);
}