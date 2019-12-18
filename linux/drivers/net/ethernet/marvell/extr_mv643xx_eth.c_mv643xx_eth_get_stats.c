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
struct tx_queue {scalar_t__ tx_dropped; scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct net_device_stats {unsigned long tx_packets; unsigned long tx_bytes; unsigned long tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct mv643xx_eth_private {int txq_count; struct tx_queue* txq; } ;

/* Variables and functions */
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *mv643xx_eth_get_stats(struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	unsigned long tx_packets = 0;
	unsigned long tx_bytes = 0;
	unsigned long tx_dropped = 0;
	int i;

	for (i = 0; i < mp->txq_count; i++) {
		struct tx_queue *txq = mp->txq + i;

		tx_packets += txq->tx_packets;
		tx_bytes += txq->tx_bytes;
		tx_dropped += txq->tx_dropped;
	}

	stats->tx_packets = tx_packets;
	stats->tx_bytes = tx_bytes;
	stats->tx_dropped = tx_dropped;

	return stats;
}