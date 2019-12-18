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
struct mlx4_dev {TYPE_3__* persist; } ;
struct mlx4_priv {struct mlx4_dev dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vbool; } ;
struct devlink_param_gset_ctx {TYPE_1__ val; } ;
struct devlink {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  snapshot_enable; } ;
struct TYPE_6__ {TYPE_2__ crdump; } ;

/* Variables and functions */
 struct mlx4_priv* devlink_priv (struct devlink*) ; 

__attribute__((used)) static int mlx4_devlink_crdump_snapshot_get(struct devlink *devlink, u32 id,
					    struct devlink_param_gset_ctx *ctx)
{
	struct mlx4_priv *priv = devlink_priv(devlink);
	struct mlx4_dev *dev = &priv->dev;

	ctx->val.vbool = dev->persist->crdump.snapshot_enable;
	return 0;
}