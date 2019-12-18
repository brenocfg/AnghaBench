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
struct mlxsw_sp_acl_tcam_region {int dummy; } ;
struct mlxsw_sp1_acl_tcam_region {int /*<<< orphan*/  cregion; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp1_acl_ctcam_region_catchall_add (struct mlxsw_sp*,struct mlxsw_sp1_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp1_acl_ctcam_region_ops ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_region_fini (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_acl_ctcam_region_init (struct mlxsw_sp*,int /*<<< orphan*/ *,struct mlxsw_sp_acl_tcam_region*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp1_acl_tcam_region_init(struct mlxsw_sp *mlxsw_sp, void *region_priv,
			       void *tcam_priv,
			       struct mlxsw_sp_acl_tcam_region *_region,
			       void *hints_priv)
{
	struct mlxsw_sp1_acl_tcam_region *region = region_priv;
	int err;

	err = mlxsw_sp_acl_ctcam_region_init(mlxsw_sp, &region->cregion,
					     _region,
					     &mlxsw_sp1_acl_ctcam_region_ops);
	if (err)
		return err;
	err = mlxsw_sp1_acl_ctcam_region_catchall_add(mlxsw_sp, region);
	if (err)
		goto err_catchall_add;
	region->region = _region;
	return 0;

err_catchall_add:
	mlxsw_sp_acl_ctcam_region_fini(&region->cregion);
	return err;
}