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
typedef  int u8 ;
struct mlxsw_sp_acl_erp_table {int base_index; struct mlxsw_sp_acl_erp_core* erp_core; } ;
struct mlxsw_sp_acl_erp_core {int num_erp_banks; } ;
struct mlxsw_sp_acl_erp {int index; } ;

/* Variables and functions */
 unsigned int mlxsw_sp_acl_erp_table_entry_size (struct mlxsw_sp_acl_erp_table const*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_table_locate(const struct mlxsw_sp_acl_erp_table *erp_table,
			      const struct mlxsw_sp_acl_erp *erp,
			      u8 *p_erpt_bank, u8 *p_erpt_index)
{
	unsigned int entry_size = mlxsw_sp_acl_erp_table_entry_size(erp_table);
	struct mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;
	unsigned int row;

	*p_erpt_bank = erp->index % erp_core->num_erp_banks;
	row = erp->index / erp_core->num_erp_banks;
	*p_erpt_index = erp_table->base_index + row * entry_size;
}