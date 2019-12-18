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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct mlx5e_sw_stats {int /*<<< orphan*/  tx_queue_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_2__ {struct mlx5e_sw_stats sw; } ;
struct mlx5e_priv {TYPE_1__ stats; } ;

/* Variables and functions */
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_grp_sw_update_stats (struct mlx5e_priv*) ; 

void mlx5i_get_stats(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct mlx5e_priv     *priv   = mlx5i_epriv(dev);
	struct mlx5e_sw_stats *sstats = &priv->stats.sw;

	mlx5i_grp_sw_update_stats(priv);

	stats->rx_packets = sstats->rx_packets;
	stats->rx_bytes   = sstats->rx_bytes;
	stats->tx_packets = sstats->tx_packets;
	stats->tx_bytes   = sstats->tx_bytes;
	stats->tx_dropped = sstats->tx_queue_dropped;
}