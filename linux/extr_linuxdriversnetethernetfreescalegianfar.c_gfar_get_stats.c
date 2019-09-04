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
struct net_device_stats {unsigned long rx_packets; unsigned long rx_bytes; unsigned long rx_dropped; unsigned long tx_bytes; unsigned long tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct gfar_private {int num_rx_queues; int num_tx_queues; TYPE_4__** tx_queue; TYPE_2__** rx_queue; } ;
struct TYPE_7__ {scalar_t__ tx_packets; scalar_t__ tx_bytes; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;
struct TYPE_5__ {scalar_t__ rx_dropped; scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 struct gfar_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *gfar_get_stats(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	unsigned long rx_packets = 0, rx_bytes = 0, rx_dropped = 0;
	unsigned long tx_packets = 0, tx_bytes = 0;
	int i;

	for (i = 0; i < priv->num_rx_queues; i++) {
		rx_packets += priv->rx_queue[i]->stats.rx_packets;
		rx_bytes   += priv->rx_queue[i]->stats.rx_bytes;
		rx_dropped += priv->rx_queue[i]->stats.rx_dropped;
	}

	dev->stats.rx_packets = rx_packets;
	dev->stats.rx_bytes   = rx_bytes;
	dev->stats.rx_dropped = rx_dropped;

	for (i = 0; i < priv->num_tx_queues; i++) {
		tx_bytes += priv->tx_queue[i]->stats.tx_bytes;
		tx_packets += priv->tx_queue[i]->stats.tx_packets;
	}

	dev->stats.tx_bytes   = tx_bytes;
	dev->stats.tx_packets = tx_packets;

	return &dev->stats;
}