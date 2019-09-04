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
typedef  scalar_t__ u32 ;
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct ixgbevf_ring {TYPE_1__ stats; int /*<<< orphan*/  syncp; } ;
struct ixgbevf_adapter {int num_tx_queues; int num_xdp_queues; int num_rx_queues; struct ixgbevf_ring** rx_ring; struct ixgbevf_ring** xdp_ring; struct ixgbevf_ring** tx_ring; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_4__ {int type; int sizeof_stat; int /*<<< orphan*/  stat_offset; } ;

/* Variables and functions */
 int IXGBEVF_GLOBAL_STATS_LEN ; 
#define  IXGBEVF_STATS 129 
#define  NETDEV_STATS 128 
 struct rtnl_link_stats64* dev_get_stats (struct net_device*,struct rtnl_link_stats64*) ; 
 TYPE_2__* ixgbevf_gstrings_stats ; 
 int /*<<< orphan*/  ixgbevf_update_stats (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void ixgbevf_get_ethtool_stats(struct net_device *netdev,
				      struct ethtool_stats *stats, u64 *data)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	struct rtnl_link_stats64 temp;
	const struct rtnl_link_stats64 *net_stats;
	unsigned int start;
	struct ixgbevf_ring *ring;
	int i, j;
	char *p;

	ixgbevf_update_stats(adapter);
	net_stats = dev_get_stats(netdev, &temp);
	for (i = 0; i < IXGBEVF_GLOBAL_STATS_LEN; i++) {
		switch (ixgbevf_gstrings_stats[i].type) {
		case NETDEV_STATS:
			p = (char *)net_stats +
					ixgbevf_gstrings_stats[i].stat_offset;
			break;
		case IXGBEVF_STATS:
			p = (char *)adapter +
					ixgbevf_gstrings_stats[i].stat_offset;
			break;
		default:
			data[i] = 0;
			continue;
		}

		data[i] = (ixgbevf_gstrings_stats[i].sizeof_stat ==
			   sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}

	/* populate Tx queue data */
	for (j = 0; j < adapter->num_tx_queues; j++) {
		ring = adapter->tx_ring[j];
		if (!ring) {
			data[i++] = 0;
			data[i++] = 0;
			continue;
		}

		do {
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i]   = ring->stats.packets;
			data[i + 1] = ring->stats.bytes;
		} while (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	}

	/* populate XDP queue data */
	for (j = 0; j < adapter->num_xdp_queues; j++) {
		ring = adapter->xdp_ring[j];
		if (!ring) {
			data[i++] = 0;
			data[i++] = 0;
			continue;
		}

		do {
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i] = ring->stats.packets;
			data[i + 1] = ring->stats.bytes;
		} while (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	}

	/* populate Rx queue data */
	for (j = 0; j < adapter->num_rx_queues; j++) {
		ring = adapter->rx_ring[j];
		if (!ring) {
			data[i++] = 0;
			data[i++] = 0;
			continue;
		}

		do {
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i]   = ring->stats.packets;
			data[i + 1] = ring->stats.bytes;
		} while (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	}
}