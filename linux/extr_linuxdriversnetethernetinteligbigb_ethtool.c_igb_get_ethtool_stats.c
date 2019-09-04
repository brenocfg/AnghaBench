#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ alloc_failed; scalar_t__ csum_err; scalar_t__ drops; scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_5__ {scalar_t__ restart_queue2; scalar_t__ restart_queue; scalar_t__ bytes; scalar_t__ packets; } ;
struct igb_ring {TYPE_2__ rx_stats; int /*<<< orphan*/  rx_syncp; TYPE_1__ tx_stats; int /*<<< orphan*/  tx_syncp2; int /*<<< orphan*/  tx_syncp; } ;
struct igb_adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/  stats64_lock; struct igb_ring** rx_ring; struct igb_ring** tx_ring; struct rtnl_link_stats64 stats64; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_8__ {int stat_offset; int sizeof_stat; } ;
struct TYPE_7__ {int stat_offset; int sizeof_stat; } ;

/* Variables and functions */
 int IGB_GLOBAL_STATS_LEN ; 
 int IGB_NETDEV_STATS_LEN ; 
 scalar_t__ IGB_RX_QUEUE_STATS_LEN ; 
 scalar_t__ IGB_TX_QUEUE_STATS_LEN ; 
 TYPE_4__* igb_gstrings_net_stats ; 
 TYPE_3__* igb_gstrings_stats ; 
 int /*<<< orphan*/  igb_update_stats (struct igb_adapter*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void igb_get_ethtool_stats(struct net_device *netdev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct rtnl_link_stats64 *net_stats = &adapter->stats64;
	unsigned int start;
	struct igb_ring *ring;
	int i, j;
	char *p;

	spin_lock(&adapter->stats64_lock);
	igb_update_stats(adapter);

	for (i = 0; i < IGB_GLOBAL_STATS_LEN; i++) {
		p = (char *)adapter + igb_gstrings_stats[i].stat_offset;
		data[i] = (igb_gstrings_stats[i].sizeof_stat ==
			sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
	for (j = 0; j < IGB_NETDEV_STATS_LEN; j++, i++) {
		p = (char *)net_stats + igb_gstrings_net_stats[j].stat_offset;
		data[i] = (igb_gstrings_net_stats[j].sizeof_stat ==
			sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
	for (j = 0; j < adapter->num_tx_queues; j++) {
		u64	restart2;

		ring = adapter->tx_ring[j];
		do {
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp);
			data[i]   = ring->tx_stats.packets;
			data[i+1] = ring->tx_stats.bytes;
			data[i+2] = ring->tx_stats.restart_queue;
		} while (u64_stats_fetch_retry_irq(&ring->tx_syncp, start));
		do {
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp2);
			restart2  = ring->tx_stats.restart_queue2;
		} while (u64_stats_fetch_retry_irq(&ring->tx_syncp2, start));
		data[i+2] += restart2;

		i += IGB_TX_QUEUE_STATS_LEN;
	}
	for (j = 0; j < adapter->num_rx_queues; j++) {
		ring = adapter->rx_ring[j];
		do {
			start = u64_stats_fetch_begin_irq(&ring->rx_syncp);
			data[i]   = ring->rx_stats.packets;
			data[i+1] = ring->rx_stats.bytes;
			data[i+2] = ring->rx_stats.drops;
			data[i+3] = ring->rx_stats.csum_err;
			data[i+4] = ring->rx_stats.alloc_failed;
		} while (u64_stats_fetch_retry_irq(&ring->rx_syncp, start));
		i += IGB_RX_QUEUE_STATS_LEN;
	}
	spin_unlock(&adapter->stats64_lock);
}