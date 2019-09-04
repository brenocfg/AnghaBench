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
struct net_device {int dummy; } ;
struct mlx5e_priv {TYPE_1__* mdev; int /*<<< orphan*/  state_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  vxlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_PORT_UP ; 
 int /*<<< orphan*/  mlx5_set_port_admin_status (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_vxlan_allowed (int /*<<< orphan*/ ) ; 
 int mlx5e_open_locked (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udp_tunnel_get_rx_info (struct net_device*) ; 

int mlx5e_open(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_open_locked(netdev);
	if (!err)
		mlx5_set_port_admin_status(priv->mdev, MLX5_PORT_UP);
	mutex_unlock(&priv->state_lock);

	if (mlx5_vxlan_allowed(priv->mdev->vxlan))
		udp_tunnel_get_rx_info(netdev);

	return err;
}