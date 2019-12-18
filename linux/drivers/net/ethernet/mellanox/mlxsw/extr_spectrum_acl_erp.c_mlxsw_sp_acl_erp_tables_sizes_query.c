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
struct mlxsw_sp_acl_erp_core {unsigned int* erpt_entries_size; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_ERPT_ENTRIES_12KB ; 
 int /*<<< orphan*/  ACL_ERPT_ENTRIES_2KB ; 
 int /*<<< orphan*/  ACL_ERPT_ENTRIES_4KB ; 
 int /*<<< orphan*/  ACL_ERPT_ENTRIES_8KB ; 
 int EIO ; 
 unsigned int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB ; 
 size_t MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB ; 
 size_t MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB ; 
 size_t MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_tables_sizes_query(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_acl_erp_core *erp_core)
{
	unsigned int size;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_2KB) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_4KB) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_8KB) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_12KB))
		return -EIO;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_2KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB] = size;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_4KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB] = size;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_8KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB] = size;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_12KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB] = size;

	return 0;
}