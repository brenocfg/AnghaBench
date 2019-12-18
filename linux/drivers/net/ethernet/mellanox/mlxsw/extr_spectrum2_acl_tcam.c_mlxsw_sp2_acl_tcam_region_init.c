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
struct mlxsw_sp2_acl_tcam_region {int /*<<< orphan*/  aregion; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp2_acl_tcam {int /*<<< orphan*/  atcam; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp2_acl_ctcam_region_ops ; 
 int mlxsw_sp_acl_atcam_region_init (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mlxsw_sp_acl_tcam_region*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp2_acl_tcam_region_init(struct mlxsw_sp *mlxsw_sp, void *region_priv,
			       void *tcam_priv,
			       struct mlxsw_sp_acl_tcam_region *_region,
			       void *hints_priv)
{
	struct mlxsw_sp2_acl_tcam_region *region = region_priv;
	struct mlxsw_sp2_acl_tcam *tcam = tcam_priv;

	region->region = _region;

	return mlxsw_sp_acl_atcam_region_init(mlxsw_sp, &tcam->atcam,
					      &region->aregion,
					      _region, hints_priv,
					      &mlxsw_sp2_acl_ctcam_region_ops);
}