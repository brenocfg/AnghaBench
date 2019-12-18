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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {scalar_t__ rx_ring_num; scalar_t__* tx_ring_num; TYPE_2__* prof; scalar_t__ port_up; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_port_profile {int num_tx_rings_p_up; int* tx_ring_num; int rx_ring_num; } ;
struct TYPE_3__ {int max_num_tx_rings_p_up; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; TYPE_1__ profile; } ;
struct ethtool_channels {int tx_count; int rx_count; } ;
struct TYPE_4__ {int num_up; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_TX_RINGS ; 
 int MLX4_EN_NUM_UP_LOW ; 
 size_t TX ; 
 size_t TX_XDP ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_priv*) ; 
 struct mlx4_en_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct mlx4_en_port_profile*,TYPE_2__*,int) ; 
 int mlx4_en_moderation_update (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_safe_replace_resources (struct mlx4_en_priv*,struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_setup_tc (struct net_device*,int) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*,int) ; 
 int mlx4_en_try_alloc_resources (struct mlx4_en_priv*,struct mlx4_en_priv*,struct mlx4_en_port_profile*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,scalar_t__) ; 

__attribute__((used)) static int mlx4_en_set_channels(struct net_device *dev,
				struct ethtool_channels *channel)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_port_profile new_prof;
	struct mlx4_en_priv *tmp;
	int port_up = 0;
	int xdp_count;
	int err = 0;
	u8 up;

	if (!channel->tx_count || !channel->rx_count)
		return -EINVAL;

	tmp = kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	mutex_lock(&mdev->state_lock);
	xdp_count = priv->tx_ring_num[TX_XDP] ? channel->rx_count : 0;
	if (channel->tx_count * priv->prof->num_up + xdp_count >
	    priv->mdev->profile.max_num_tx_rings_p_up * priv->prof->num_up) {
		err = -EINVAL;
		en_err(priv,
		       "Total number of TX and XDP rings (%d) exceeds the maximum supported (%d)\n",
		       channel->tx_count * priv->prof->num_up  + xdp_count,
		       MAX_TX_RINGS);
		goto out;
	}

	memcpy(&new_prof, priv->prof, sizeof(struct mlx4_en_port_profile));
	new_prof.num_tx_rings_p_up = channel->tx_count;
	new_prof.tx_ring_num[TX] = channel->tx_count * priv->prof->num_up;
	new_prof.tx_ring_num[TX_XDP] = xdp_count;
	new_prof.rx_ring_num = channel->rx_count;

	err = mlx4_en_try_alloc_resources(priv, tmp, &new_prof, true);
	if (err)
		goto out;

	if (priv->port_up) {
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	}

	mlx4_en_safe_replace_resources(priv, tmp);

	netif_set_real_num_rx_queues(dev, priv->rx_ring_num);

	up = (priv->prof->num_up == MLX4_EN_NUM_UP_LOW) ?
				    0 : priv->prof->num_up;
	mlx4_en_setup_tc(dev, up);

	en_warn(priv, "Using %d TX rings\n", priv->tx_ring_num[TX]);
	en_warn(priv, "Using %d RX rings\n", priv->rx_ring_num);

	if (port_up) {
		err = mlx4_en_start_port(dev);
		if (err)
			en_err(priv, "Failed starting port\n");
	}

	err = mlx4_en_moderation_update(priv);
out:
	mutex_unlock(&mdev->state_lock);
	kfree(tmp);
	return err;
}