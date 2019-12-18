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
struct TYPE_3__ {int /*<<< orphan*/  num_queues; int /*<<< orphan*/  max_queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_queues; int /*<<< orphan*/  max_queues; } ;
struct gve_priv {TYPE_1__ tx_cfg; TYPE_2__ rx_cfg; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; scalar_t__ max_combined; scalar_t__ max_other; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 struct gve_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void gve_get_channels(struct net_device *netdev,
			     struct ethtool_channels *cmd)
{
	struct gve_priv *priv = netdev_priv(netdev);

	cmd->max_rx = priv->rx_cfg.max_queues;
	cmd->max_tx = priv->tx_cfg.max_queues;
	cmd->max_other = 0;
	cmd->max_combined = 0;
	cmd->rx_count = priv->rx_cfg.num_queues;
	cmd->tx_count = priv->tx_cfg.num_queues;
	cmd->other_count = 0;
	cmd->combined_count = 0;
}