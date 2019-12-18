#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {TYPE_2__* steering; } ;
struct mlx5_core_dev {TYPE_3__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  vstr; } ;
struct devlink_param_gset_ctx {TYPE_1__ val; } ;
struct devlink {int dummy; } ;
typedef  enum mlx5_flow_steering_mode { ____Placeholder_mlx5_flow_steering_mode } mlx5_flow_steering_mode ;
struct TYPE_5__ {int mode; } ;

/* Variables and functions */
 int MLX5_FLOW_STEERING_MODE_DMFS ; 
 int MLX5_FLOW_STEERING_MODE_SMFS ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlx5_devlink_fs_mode_set(struct devlink *devlink, u32 id,
				    struct devlink_param_gset_ctx *ctx)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	enum mlx5_flow_steering_mode mode;

	if (!strcmp(ctx->val.vstr, "smfs"))
		mode = MLX5_FLOW_STEERING_MODE_SMFS;
	else
		mode = MLX5_FLOW_STEERING_MODE_DMFS;
	dev->priv.steering->mode = mode;

	return 0;
}