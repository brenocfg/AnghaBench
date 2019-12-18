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
struct net_device_stats {unsigned long rx_packets; unsigned long rx_bytes; unsigned long tx_packets; unsigned long tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
struct enetc_ndev_priv {int num_rx_rings; int num_tx_rings; TYPE_4__** tx_ring; TYPE_2__** rx_ring; } ;
struct TYPE_7__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;
struct TYPE_5__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

struct net_device_stats *enetc_get_stats(struct net_device *ndev)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	unsigned long packets = 0, bytes = 0;
	int i;

	for (i = 0; i < priv->num_rx_rings; i++) {
		packets += priv->rx_ring[i]->stats.packets;
		bytes	+= priv->rx_ring[i]->stats.bytes;
	}

	stats->rx_packets = packets;
	stats->rx_bytes = bytes;
	bytes = 0;
	packets = 0;

	for (i = 0; i < priv->num_tx_rings; i++) {
		packets += priv->tx_ring[i]->stats.packets;
		bytes	+= priv->tx_ring[i]->stats.bytes;
	}

	stats->tx_packets = packets;
	stats->tx_bytes = bytes;

	return stats;
}