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
struct mlxsw_sp_acl_tcam_vregion {TYPE_1__* region2; TYPE_1__* region; int /*<<< orphan*/  tcam; } ;
struct mlxsw_sp_acl_tcam_rehash_ctx {int this_is_rollback; void* hints_priv; } ;
typedef  void mlxsw_sp_acl_tcam_region ;
struct mlxsw_sp_acl_tcam_ops {int /*<<< orphan*/  (* region_rehash_hints_put ) (void*) ;void* (* region_rehash_hints_get ) (int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp {struct mlxsw_sp_acl_tcam_ops* acl_tcam_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  group; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int mlxsw_sp_acl_tcam_group_region_attach (struct mlxsw_sp*,int /*<<< orphan*/ ,void*,unsigned int,TYPE_1__*) ; 
 void* mlxsw_sp_acl_tcam_region_create (struct mlxsw_sp*,int /*<<< orphan*/ ,struct mlxsw_sp_acl_tcam_vregion*,void*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_region_destroy (struct mlxsw_sp*,void*) ; 
 unsigned int mlxsw_sp_acl_tcam_vregion_prio (struct mlxsw_sp_acl_tcam_vregion*) ; 
 void* stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  trace_mlxsw_sp_acl_tcam_vregion_rehash (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_vregion_rehash_start(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_tcam_vregion *vregion,
				       struct mlxsw_sp_acl_tcam_rehash_ctx *ctx)
{
	const struct mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	unsigned int priority = mlxsw_sp_acl_tcam_vregion_prio(vregion);
	struct mlxsw_sp_acl_tcam_region *new_region;
	void *hints_priv;
	int err;

	trace_mlxsw_sp_acl_tcam_vregion_rehash(mlxsw_sp, vregion);

	hints_priv = ops->region_rehash_hints_get(vregion->region->priv);
	if (IS_ERR(hints_priv))
		return PTR_ERR(hints_priv);

	new_region = mlxsw_sp_acl_tcam_region_create(mlxsw_sp, vregion->tcam,
						     vregion, hints_priv);
	if (IS_ERR(new_region)) {
		err = PTR_ERR(new_region);
		goto err_region_create;
	}

	/* vregion->region contains the pointer to the new region
	 * we are going to migrate to.
	 */
	vregion->region2 = vregion->region;
	vregion->region = new_region;
	err = mlxsw_sp_acl_tcam_group_region_attach(mlxsw_sp,
						    vregion->region2->group,
						    new_region, priority,
						    vregion->region2);
	if (err)
		goto err_group_region_attach;

	ctx->hints_priv = hints_priv;
	ctx->this_is_rollback = false;

	return 0;

err_group_region_attach:
	vregion->region = vregion->region2;
	vregion->region2 = NULL;
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, new_region);
err_region_create:
	ops->region_rehash_hints_put(hints_priv);
	return err;
}