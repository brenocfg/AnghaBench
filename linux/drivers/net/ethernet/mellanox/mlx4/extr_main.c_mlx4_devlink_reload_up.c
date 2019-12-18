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
struct netlink_ext_ack {int dummy; } ;
struct mlx4_dev {struct mlx4_dev_persistent* persist; } ;
struct mlx4_priv {struct mlx4_dev dev; } ;
struct mlx4_dev_persistent {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct mlx4_priv* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mlx4_err (int /*<<< orphan*/ ,char*,int) ; 
 int mlx4_restart_one_up (int /*<<< orphan*/ ,int,struct devlink*) ; 

__attribute__((used)) static int mlx4_devlink_reload_up(struct devlink *devlink,
				  struct netlink_ext_ack *extack)
{
	struct mlx4_priv *priv = devlink_priv(devlink);
	struct mlx4_dev *dev = &priv->dev;
	struct mlx4_dev_persistent *persist = dev->persist;
	int err;

	err = mlx4_restart_one_up(persist->pdev, true, devlink);
	if (err)
		mlx4_err(persist->dev, "mlx4_restart_one_up failed, ret=%d\n",
			 err);

	return err;
}