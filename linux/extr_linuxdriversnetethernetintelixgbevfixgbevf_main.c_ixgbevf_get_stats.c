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
typedef  scalar_t__ u64 ;
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; scalar_t__ multicast; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ packets; scalar_t__ bytes; } ;
struct ixgbevf_ring {TYPE_2__ stats; int /*<<< orphan*/  syncp; } ;
struct TYPE_3__ {scalar_t__ base_vfmprc; scalar_t__ vfmprc; } ;
struct ixgbevf_adapter {int num_rx_queues; int num_tx_queues; int num_xdp_queues; struct ixgbevf_ring** xdp_ring; struct ixgbevf_ring** tx_ring; struct ixgbevf_ring** rx_ring; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbevf_get_tx_ring_stats (struct rtnl_link_stats64*,struct ixgbevf_ring const*) ; 
 int /*<<< orphan*/  ixgbevf_update_stats (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void ixgbevf_get_stats(struct net_device *netdev,
			      struct rtnl_link_stats64 *stats)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	unsigned int start;
	u64 bytes, packets;
	const struct ixgbevf_ring *ring;
	int i;

	ixgbevf_update_stats(adapter);

	stats->multicast = adapter->stats.vfmprc - adapter->stats.base_vfmprc;

	rcu_read_lock();
	for (i = 0; i < adapter->num_rx_queues; i++) {
		ring = adapter->rx_ring[i];
		do {
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			bytes = ring->stats.bytes;
			packets = ring->stats.packets;
		} while (u64_stats_fetch_retry_irq(&ring->syncp, start));
		stats->rx_bytes += bytes;
		stats->rx_packets += packets;
	}

	for (i = 0; i < adapter->num_tx_queues; i++) {
		ring = adapter->tx_ring[i];
		ixgbevf_get_tx_ring_stats(stats, ring);
	}

	for (i = 0; i < adapter->num_xdp_queues; i++) {
		ring = adapter->xdp_ring[i];
		ixgbevf_get_tx_ring_stats(stats, ring);
	}
	rcu_read_unlock();
}