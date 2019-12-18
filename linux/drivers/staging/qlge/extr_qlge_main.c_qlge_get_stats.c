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
struct tx_ring {scalar_t__ tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct rx_ring {scalar_t__ rx_multicast; scalar_t__ rx_errors; scalar_t__ rx_dropped; scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;
struct ql_adapter {int rss_ring_count; int tx_ring_count; struct tx_ring* tx_ring; struct rx_ring* rx_ring; } ;
struct net_device_stats {unsigned long rx_packets; unsigned long rx_bytes; unsigned long rx_dropped; unsigned long rx_errors; unsigned long multicast; unsigned long tx_packets; unsigned long tx_bytes; unsigned long tx_errors; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 struct ql_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *qlge_get_stats(struct net_device
					       *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	struct rx_ring *rx_ring = &qdev->rx_ring[0];
	struct tx_ring *tx_ring = &qdev->tx_ring[0];
	unsigned long pkts, mcast, dropped, errors, bytes;
	int i;

	/* Get RX stats. */
	pkts = mcast = dropped = errors = bytes = 0;
	for (i = 0; i < qdev->rss_ring_count; i++, rx_ring++) {
			pkts += rx_ring->rx_packets;
			bytes += rx_ring->rx_bytes;
			dropped += rx_ring->rx_dropped;
			errors += rx_ring->rx_errors;
			mcast += rx_ring->rx_multicast;
	}
	ndev->stats.rx_packets = pkts;
	ndev->stats.rx_bytes = bytes;
	ndev->stats.rx_dropped = dropped;
	ndev->stats.rx_errors = errors;
	ndev->stats.multicast = mcast;

	/* Get TX stats. */
	pkts = errors = bytes = 0;
	for (i = 0; i < qdev->tx_ring_count; i++, tx_ring++) {
			pkts += tx_ring->tx_packets;
			bytes += tx_ring->tx_bytes;
			errors += tx_ring->tx_errors;
	}
	ndev->stats.tx_packets = pkts;
	ndev->stats.tx_bytes = bytes;
	ndev->stats.tx_errors = errors;
	return &ndev->stats;
}