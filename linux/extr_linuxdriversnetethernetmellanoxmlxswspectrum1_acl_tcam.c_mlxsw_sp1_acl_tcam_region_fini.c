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
struct mlxsw_sp1_acl_tcam_region {int /*<<< orphan*/  cregion; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp1_acl_ctcam_region_catchall_del (struct mlxsw_sp*,struct mlxsw_sp1_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_region_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp1_acl_tcam_region_fini(struct mlxsw_sp *mlxsw_sp, void *region_priv)
{
	struct mlxsw_sp1_acl_tcam_region *region = region_priv;

	mlxsw_sp1_acl_ctcam_region_catchall_del(mlxsw_sp, region);
	mlxsw_sp_acl_ctcam_region_fini(&region->cregion);
}