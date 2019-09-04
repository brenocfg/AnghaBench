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
struct mlxsw_sp_acl_atcam_region {int /*<<< orphan*/  erp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_erp_table_destroy (int /*<<< orphan*/ ) ; 

void mlxsw_sp_acl_erp_region_fini(struct mlxsw_sp_acl_atcam_region *aregion)
{
	mlxsw_sp_acl_erp_table_destroy(aregion->erp_table);
}