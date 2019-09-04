#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int vlan_strip_disable; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_2__ channels; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int mlx5e_modify_channels_vsd (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_feature_rx_vlan(struct net_device *netdev, bool enable)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int err = 0;

	mutex_lock(&priv->state_lock);

	priv->channels.params.vlan_strip_disable = !enable;
	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		goto unlock;

	err = mlx5e_modify_channels_vsd(&priv->channels, !enable);
	if (err)
		priv->channels.params.vlan_strip_disable = enable;

unlock:
	mutex_unlock(&priv->state_lock);

	return err;
}