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
struct rtnl_link_stats64 {int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  dropped; int /*<<< orphan*/  errors; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  syncp; } ;
struct TYPE_3__ {int /*<<< orphan*/  fifo_errors; int /*<<< orphan*/  dropped; int /*<<< orphan*/  errors; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; int /*<<< orphan*/  syncp; } ;
struct ave_private {TYPE_2__ stats_tx; TYPE_1__ stats_rx; } ;

/* Variables and functions */
 struct ave_private* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void ave_get_stats64(struct net_device *ndev,
			    struct rtnl_link_stats64 *stats)
{
	struct ave_private *priv = netdev_priv(ndev);
	unsigned int start;

	do {
		start = u64_stats_fetch_begin_irq(&priv->stats_rx.syncp);
		stats->rx_packets = priv->stats_rx.packets;
		stats->rx_bytes	  = priv->stats_rx.bytes;
	} while (u64_stats_fetch_retry_irq(&priv->stats_rx.syncp, start));

	do {
		start = u64_stats_fetch_begin_irq(&priv->stats_tx.syncp);
		stats->tx_packets = priv->stats_tx.packets;
		stats->tx_bytes	  = priv->stats_tx.bytes;
	} while (u64_stats_fetch_retry_irq(&priv->stats_tx.syncp, start));

	stats->rx_errors      = priv->stats_rx.errors;
	stats->tx_errors      = priv->stats_tx.errors;
	stats->rx_dropped     = priv->stats_rx.dropped;
	stats->tx_dropped     = priv->stats_tx.dropped;
	stats->rx_fifo_errors = priv->stats_rx.fifo_errors;
	stats->collisions     = priv->stats_tx.collisions;
}