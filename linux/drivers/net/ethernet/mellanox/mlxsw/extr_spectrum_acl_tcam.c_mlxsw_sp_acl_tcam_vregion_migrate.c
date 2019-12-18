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
struct mlxsw_sp_acl_tcam_vregion {int /*<<< orphan*/  lock; int /*<<< orphan*/  region2; int /*<<< orphan*/  region; } ;
struct mlxsw_sp_acl_tcam_rehash_ctx {int this_is_rollback; int /*<<< orphan*/ * current_vchunk; } ;
struct mlxsw_sp {TYPE_1__* bus_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_acl_tcam_vchunk_migrate_all (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*,struct mlxsw_sp_acl_tcam_rehash_ctx*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mlxsw_sp_acl_tcam_vregion_migrate (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  trace_mlxsw_sp_acl_tcam_vregion_migrate_end (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 
 int /*<<< orphan*/  trace_mlxsw_sp_acl_tcam_vregion_rehash_rollback_failed (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_vregion_migrate(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_acl_tcam_vregion *vregion,
				  struct mlxsw_sp_acl_tcam_rehash_ctx *ctx,
				  int *credits)
{
	int err, err2;

	trace_mlxsw_sp_acl_tcam_vregion_migrate(mlxsw_sp, vregion);
	mutex_lock(&vregion->lock);
	err = mlxsw_sp_acl_tcam_vchunk_migrate_all(mlxsw_sp, vregion,
						   ctx, credits);
	if (err) {
		/* In case migration was not successful, we need to swap
		 * so the original region pointer is assigned again
		 * to vregion->region.
		 */
		swap(vregion->region, vregion->region2);
		ctx->current_vchunk = NULL;
		ctx->this_is_rollback = true;
		err2 = mlxsw_sp_acl_tcam_vchunk_migrate_all(mlxsw_sp, vregion,
							    ctx, credits);
		if (err2) {
			trace_mlxsw_sp_acl_tcam_vregion_rehash_rollback_failed(mlxsw_sp,
									       vregion);
			dev_err(mlxsw_sp->bus_info->dev, "Failed to rollback during vregion migration fail\n");
			/* Let the rollback to be continued later on. */
		}
	}
	mutex_unlock(&vregion->lock);
	trace_mlxsw_sp_acl_tcam_vregion_migrate_end(mlxsw_sp, vregion);
	return err;
}