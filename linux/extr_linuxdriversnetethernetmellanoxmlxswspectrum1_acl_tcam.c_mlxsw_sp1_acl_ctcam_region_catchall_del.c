#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cchunk; int /*<<< orphan*/  centry; struct mlxsw_sp_acl_rule_info* rulei; } ;
struct mlxsw_sp1_acl_tcam_region {TYPE_1__ catchall; int /*<<< orphan*/  cregion; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_chunk_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_entry_del (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_destroy (struct mlxsw_sp_acl_rule_info*) ; 

__attribute__((used)) static void
mlxsw_sp1_acl_ctcam_region_catchall_del(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp1_acl_tcam_region *region)
{
	struct mlxsw_sp_acl_rule_info *rulei = region->catchall.rulei;

	mlxsw_sp_acl_ctcam_entry_del(mlxsw_sp, &region->cregion,
				     &region->catchall.cchunk,
				     &region->catchall.centry);
	mlxsw_sp_acl_rulei_destroy(rulei);
	mlxsw_sp_acl_ctcam_chunk_fini(&region->catchall.cchunk);
}