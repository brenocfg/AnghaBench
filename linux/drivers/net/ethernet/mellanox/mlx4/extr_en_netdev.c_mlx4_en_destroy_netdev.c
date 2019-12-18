#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlx4_en_priv {size_t port; int /*<<< orphan*/  service_task; int /*<<< orphan*/  stats_task; int /*<<< orphan*/  res; scalar_t__ allocated; scalar_t__ registered; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/ ** upper; int /*<<< orphan*/ ** pndev; TYPE_2__* dev; int /*<<< orphan*/  workqueue; } ;
struct TYPE_4__ {int flags2; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int MLX4_DEV_CAP_FLAG2_TS ; 
 int /*<<< orphan*/  MLX4_EN_PAGE_SIZE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_port_type_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,size_t) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_cleanup_filters (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_free_resources (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_remove_timestamp (struct mlx4_en_dev*) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_get_devlink_port (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void mlx4_en_destroy_netdev(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;

	en_dbg(DRV, priv, "Destroying netdev on port:%d\n", priv->port);

	/* Unregister device - this will close the port if it was up */
	if (priv->registered) {
		devlink_port_type_clear(mlx4_get_devlink_port(mdev->dev,
							      priv->port));
		unregister_netdev(dev);
	}

	if (priv->allocated)
		mlx4_free_hwq_res(mdev->dev, &priv->res, MLX4_EN_PAGE_SIZE);

	cancel_delayed_work(&priv->stats_task);
	cancel_delayed_work(&priv->service_task);
	/* flush any pending task for this netdev */
	flush_workqueue(mdev->workqueue);

	if (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS)
		mlx4_en_remove_timestamp(mdev);

	/* Detach the netdev so tasks would not attempt to access it */
	mutex_lock(&mdev->state_lock);
	mdev->pndev[priv->port] = NULL;
	mdev->upper[priv->port] = NULL;

#ifdef CONFIG_RFS_ACCEL
	mlx4_en_cleanup_filters(priv);
#endif

	mlx4_en_free_resources(priv);
	mutex_unlock(&mdev->state_lock);

	free_netdev(dev);
}