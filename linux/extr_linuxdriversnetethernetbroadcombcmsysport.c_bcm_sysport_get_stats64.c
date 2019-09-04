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
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {int /*<<< orphan*/  stats; } ;
struct bcm_sysport_stats64 {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  syncp; struct bcm_sysport_stats64 stats64; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_sysport_update_tx_stats (struct bcm_sysport_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_stats_to_stats64 (struct rtnl_link_stats64*,int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void bcm_sysport_get_stats64(struct net_device *dev,
				    struct rtnl_link_stats64 *stats)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct bcm_sysport_stats64 *stats64 = &priv->stats64;
	unsigned int start;

	netdev_stats_to_stats64(stats, &dev->stats);

	bcm_sysport_update_tx_stats(priv, &stats->tx_bytes,
				    &stats->tx_packets);

	do {
		start = u64_stats_fetch_begin_irq(&priv->syncp);
		stats->rx_packets = stats64->rx_packets;
		stats->rx_bytes = stats64->rx_bytes;
	} while (u64_stats_fetch_retry_irq(&priv->syncp, start));
}