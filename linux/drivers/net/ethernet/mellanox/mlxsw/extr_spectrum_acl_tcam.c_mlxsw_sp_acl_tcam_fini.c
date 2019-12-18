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
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  (* fini ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_acl_tcam {int /*<<< orphan*/  used_regions; int /*<<< orphan*/  used_groups; int /*<<< orphan*/  priv; int /*<<< orphan*/  lock; } ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

void mlxsw_sp_acl_tcam_fini(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_tcam *tcam)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	mutex_destroy(&tcam->lock);
	ops->fini(mlxsw_sp, tcam->priv);
	kfree(tcam->used_groups);
	kfree(tcam->used_regions);
}