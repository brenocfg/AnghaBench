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
struct mlxsw_sp_acl_erp_core {unsigned int num_erp_banks; unsigned int* erpt_entries_size; int /*<<< orphan*/  erp_tables; } ;
typedef  enum mlxsw_sp_acl_atcam_region_type { ____Placeholder_mlxsw_sp_acl_atcam_region_type } mlxsw_sp_acl_atcam_region_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 scalar_t__ MLXSW_SP_ACL_ERP_GENALLOC_OFFSET ; 
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_table_alloc(struct mlxsw_sp_acl_erp_core *erp_core,
			     unsigned int num_erps,
			     enum mlxsw_sp_acl_atcam_region_type region_type,
			     unsigned long *p_index)
{
	unsigned int num_rows, entry_size;

	/* We only allow allocations of entire rows */
	if (num_erps % erp_core->num_erp_banks != 0)
		return -EINVAL;

	entry_size = erp_core->erpt_entries_size[region_type];
	num_rows = num_erps / erp_core->num_erp_banks;

	*p_index = gen_pool_alloc(erp_core->erp_tables, num_rows * entry_size);
	if (*p_index == 0)
		return -ENOBUFS;
	*p_index -= MLXSW_SP_ACL_ERP_GENALLOC_OFFSET;

	return 0;
}