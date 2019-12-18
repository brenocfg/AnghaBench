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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  id; TYPE_1__* group; int /*<<< orphan*/  priv; } ;
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  (* region_fini ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_disable (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_free (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_region*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_id_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_region_destroy(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_tcam_region *region)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	ops->region_fini(mlxsw_sp, region->priv);
	mlxsw_sp_acl_tcam_region_disable(mlxsw_sp, region);
	mlxsw_sp_acl_tcam_region_free(mlxsw_sp, region);
	mlxsw_sp_acl_tcam_region_id_put(region->group->tcam,
					region->id);
	kfree(region);
}