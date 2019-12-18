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
struct mlx4_dev_persistent {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; scalar_t__ num_vfs; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct mlx4_priv* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mlx4_restart_one_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlx4_devlink_reload_down(struct devlink *devlink,
				    struct netlink_ext_ack *extack)
{
	struct mlx4_priv *priv = devlink_priv(devlink);
	struct mlx4_dev *dev = &priv->dev;
	struct mlx4_dev_persistent *persist = dev->persist;

	if (persist->num_vfs)
		mlx4_warn(persist->dev, "Reload performed on PF, will cause reset on operating Virtual Functions\n");
	mlx4_restart_one_down(persist->pdev);
	return 0;
}