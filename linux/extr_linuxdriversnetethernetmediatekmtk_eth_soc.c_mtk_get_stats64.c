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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct mtk_mac {struct mtk_hw_stats* hw_stats; } ;
struct mtk_hw_stats {int /*<<< orphan*/  tx_skip; int /*<<< orphan*/  rx_checksum_errors; int /*<<< orphan*/  rx_fcs_errors; int /*<<< orphan*/  rx_overflow; scalar_t__ rx_long_errors; scalar_t__ rx_short_errors; int /*<<< orphan*/  tx_collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  syncp; int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_stats_update_mac (struct mtk_mac*) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mtk_get_stats64(struct net_device *dev,
			    struct rtnl_link_stats64 *storage)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_hw_stats *hw_stats = mac->hw_stats;
	unsigned int start;

	if (netif_running(dev) && netif_device_present(dev)) {
		if (spin_trylock_bh(&hw_stats->stats_lock)) {
			mtk_stats_update_mac(mac);
			spin_unlock_bh(&hw_stats->stats_lock);
		}
	}

	do {
		start = u64_stats_fetch_begin_irq(&hw_stats->syncp);
		storage->rx_packets = hw_stats->rx_packets;
		storage->tx_packets = hw_stats->tx_packets;
		storage->rx_bytes = hw_stats->rx_bytes;
		storage->tx_bytes = hw_stats->tx_bytes;
		storage->collisions = hw_stats->tx_collisions;
		storage->rx_length_errors = hw_stats->rx_short_errors +
			hw_stats->rx_long_errors;
		storage->rx_over_errors = hw_stats->rx_overflow;
		storage->rx_crc_errors = hw_stats->rx_fcs_errors;
		storage->rx_errors = hw_stats->rx_checksum_errors;
		storage->tx_aborted_errors = hw_stats->tx_skip;
	} while (u64_stats_fetch_retry_irq(&hw_stats->syncp, start));

	storage->tx_errors = dev->stats.tx_errors;
	storage->rx_dropped = dev->stats.rx_dropped;
	storage->tx_dropped = dev->stats.tx_dropped;
}