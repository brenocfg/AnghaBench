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
struct net_device_stats {unsigned long tx_bytes; unsigned long tx_packets; unsigned long rx_bytes; unsigned long rx_packets; unsigned long rx_errors; unsigned long rx_missed_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct bcmgenet_tx_ring {scalar_t__ packets; scalar_t__ bytes; } ;
struct bcmgenet_rx_ring {scalar_t__ dropped; scalar_t__ errors; scalar_t__ packets; scalar_t__ bytes; } ;
struct bcmgenet_priv {struct bcmgenet_rx_ring* rx_rings; TYPE_1__* hw_params; struct bcmgenet_tx_ring* tx_rings; } ;
struct TYPE_2__ {unsigned int tx_queues; unsigned int rx_queues; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *bcmgenet_get_stats(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	unsigned long tx_bytes = 0, tx_packets = 0;
	unsigned long rx_bytes = 0, rx_packets = 0;
	unsigned long rx_errors = 0, rx_dropped = 0;
	struct bcmgenet_tx_ring *tx_ring;
	struct bcmgenet_rx_ring *rx_ring;
	unsigned int q;

	for (q = 0; q < priv->hw_params->tx_queues; q++) {
		tx_ring = &priv->tx_rings[q];
		tx_bytes += tx_ring->bytes;
		tx_packets += tx_ring->packets;
	}
	tx_ring = &priv->tx_rings[DESC_INDEX];
	tx_bytes += tx_ring->bytes;
	tx_packets += tx_ring->packets;

	for (q = 0; q < priv->hw_params->rx_queues; q++) {
		rx_ring = &priv->rx_rings[q];

		rx_bytes += rx_ring->bytes;
		rx_packets += rx_ring->packets;
		rx_errors += rx_ring->errors;
		rx_dropped += rx_ring->dropped;
	}
	rx_ring = &priv->rx_rings[DESC_INDEX];
	rx_bytes += rx_ring->bytes;
	rx_packets += rx_ring->packets;
	rx_errors += rx_ring->errors;
	rx_dropped += rx_ring->dropped;

	dev->stats.tx_bytes = tx_bytes;
	dev->stats.tx_packets = tx_packets;
	dev->stats.rx_bytes = rx_bytes;
	dev->stats.rx_packets = rx_packets;
	dev->stats.rx_errors = rx_errors;
	dev->stats.rx_missed_errors = rx_errors;
	return &dev->stats;
}