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
struct mlxsw_sp_acl_erp_table {struct mlxsw_sp_acl_erp_core* erp_core; struct mlxsw_sp_acl_atcam_region* aregion; } ;
struct mlxsw_sp_acl_erp_core {unsigned int* erpt_entries_size; } ;
struct mlxsw_sp_acl_atcam_region {size_t type; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
mlxsw_sp_acl_erp_table_entry_size(const struct mlxsw_sp_acl_erp_table *erp_table)
{
	struct mlxsw_sp_acl_atcam_region *aregion = erp_table->aregion;
	struct mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;

	return erp_core->erpt_entries_size[aregion->type];
}