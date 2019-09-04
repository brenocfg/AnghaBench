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
typedef  scalar_t__ u64 ;
struct rtnl_link_stats64 {scalar_t__ tx_errors; scalar_t__ rx_errors; scalar_t__ tx_window_errors; scalar_t__ rx_missed_errors; scalar_t__ rx_fifo_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ collisions; scalar_t__ multicast; scalar_t__ rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ bytes; scalar_t__ cnt; } ;
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ cnt; } ;
struct ena_ring {TYPE_2__ rx_stats; int /*<<< orphan*/  syncp; TYPE_1__ tx_stats; } ;
struct TYPE_6__ {scalar_t__ rx_drops; } ;
struct ena_adapter {int num_queues; TYPE_3__ dev_stats; int /*<<< orphan*/  syncp; struct ena_ring* rx_ring; struct ena_ring* tx_ring; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void ena_get_stats64(struct net_device *netdev,
			    struct rtnl_link_stats64 *stats)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	struct ena_ring *rx_ring, *tx_ring;
	unsigned int start;
	u64 rx_drops;
	int i;

	if (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		return;

	for (i = 0; i < adapter->num_queues; i++) {
		u64 bytes, packets;

		tx_ring = &adapter->tx_ring[i];

		do {
			start = u64_stats_fetch_begin_irq(&tx_ring->syncp);
			packets = tx_ring->tx_stats.cnt;
			bytes = tx_ring->tx_stats.bytes;
		} while (u64_stats_fetch_retry_irq(&tx_ring->syncp, start));

		stats->tx_packets += packets;
		stats->tx_bytes += bytes;

		rx_ring = &adapter->rx_ring[i];

		do {
			start = u64_stats_fetch_begin_irq(&rx_ring->syncp);
			packets = rx_ring->rx_stats.cnt;
			bytes = rx_ring->rx_stats.bytes;
		} while (u64_stats_fetch_retry_irq(&rx_ring->syncp, start));

		stats->rx_packets += packets;
		stats->rx_bytes += bytes;
	}

	do {
		start = u64_stats_fetch_begin_irq(&adapter->syncp);
		rx_drops = adapter->dev_stats.rx_drops;
	} while (u64_stats_fetch_retry_irq(&adapter->syncp, start));

	stats->rx_dropped = rx_drops;

	stats->multicast = 0;
	stats->collisions = 0;

	stats->rx_length_errors = 0;
	stats->rx_crc_errors = 0;
	stats->rx_frame_errors = 0;
	stats->rx_fifo_errors = 0;
	stats->rx_missed_errors = 0;
	stats->tx_window_errors = 0;

	stats->rx_errors = 0;
	stats->tx_errors = 0;
}