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
struct mlxsw_sp_acl_erp_table {int num_ctcam_erps; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_enable (struct mlxsw_sp_acl_erp_table*,int) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_region_ctcam_disable(struct mlxsw_sp_acl_erp_table *erp_table)
{
	/* Only disable C-TCAM lookup when last C-TCAM eRP is deleted */
	if (erp_table->num_ctcam_erps > 1)
		return;

	mlxsw_sp_acl_erp_table_enable(erp_table, false);
}