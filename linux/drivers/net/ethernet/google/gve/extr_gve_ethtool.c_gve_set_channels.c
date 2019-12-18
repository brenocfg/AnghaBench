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
struct net_device {int dummy; } ;
struct gve_queue_config {int num_queues; } ;
struct gve_priv {struct gve_queue_config rx_cfg; struct gve_queue_config tx_cfg; } ;
struct ethtool_channels {int tx_count; int rx_count; scalar_t__ combined_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int gve_adjust_queues (struct gve_priv*,struct gve_queue_config,struct gve_queue_config) ; 
 int /*<<< orphan*/  gve_get_channels (struct net_device*,struct ethtool_channels*) ; 
 struct gve_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int gve_set_channels(struct net_device *netdev,
			    struct ethtool_channels *cmd)
{
	struct gve_priv *priv = netdev_priv(netdev);
	struct gve_queue_config new_tx_cfg = priv->tx_cfg;
	struct gve_queue_config new_rx_cfg = priv->rx_cfg;
	struct ethtool_channels old_settings;
	int new_tx = cmd->tx_count;
	int new_rx = cmd->rx_count;

	gve_get_channels(netdev, &old_settings);

	/* Changing combined is not allowed allowed */
	if (cmd->combined_count != old_settings.combined_count)
		return -EINVAL;

	if (!new_rx || !new_tx)
		return -EINVAL;

	if (!netif_carrier_ok(netdev)) {
		priv->tx_cfg.num_queues = new_tx;
		priv->rx_cfg.num_queues = new_rx;
		return 0;
	}

	new_tx_cfg.num_queues = new_tx;
	new_rx_cfg.num_queues = new_rx;

	return gve_adjust_queues(priv, new_rx_cfg, new_tx_cfg);
}