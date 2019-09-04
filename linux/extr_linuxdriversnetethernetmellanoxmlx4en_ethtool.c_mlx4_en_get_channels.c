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
struct net_device {int dummy; } ;
struct mlx4_en_priv {int* tx_ring_num; TYPE_1__* prof; int /*<<< orphan*/  rx_ring_num; TYPE_3__* mdev; } ;
struct ethtool_channels {int tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_num_tx_rings_p_up; } ;
struct TYPE_6__ {TYPE_2__ profile; } ;
struct TYPE_4__ {int num_up; } ;

/* Variables and functions */
 size_t TX ; 
 int /*<<< orphan*/  mlx4_en_get_max_num_rx_rings (struct net_device*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_get_channels(struct net_device *dev,
				 struct ethtool_channels *channel)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	channel->max_rx = mlx4_en_get_max_num_rx_rings(dev);
	channel->max_tx = priv->mdev->profile.max_num_tx_rings_p_up;

	channel->rx_count = priv->rx_ring_num;
	channel->tx_count = priv->tx_ring_num[TX] /
			    priv->prof->num_up;
}