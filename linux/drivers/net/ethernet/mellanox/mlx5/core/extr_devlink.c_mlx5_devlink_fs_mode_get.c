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
struct TYPE_5__ {TYPE_1__* steering; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  vstr; } ;
struct devlink_param_gset_ctx {TYPE_3__ val; } ;
struct devlink {int dummy; } ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ MLX5_FLOW_STEERING_MODE_SMFS ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlx5_devlink_fs_mode_get(struct devlink *devlink, u32 id,
				    struct devlink_param_gset_ctx *ctx)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);

	if (dev->priv.steering->mode == MLX5_FLOW_STEERING_MODE_SMFS)
		strcpy(ctx->val.vstr, "smfs");
	else
		strcpy(ctx->val.vstr, "dmfs");
	return 0;
}