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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vu32; } ;
struct devlink_param_gset_ctx {TYPE_1__ val; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int mlxsw_sp_acl_region_rehash_intrvl_set (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_params_acl_region_rehash_intrvl_set(struct devlink *devlink, u32 id,
					     struct devlink_param_gset_ctx *ctx)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	return mlxsw_sp_acl_region_rehash_intrvl_set(mlxsw_sp, ctx->val.vu32);
}