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
typedef  scalar_t__ u64 ;
struct bcm_sysport_tx_ring {scalar_t__ packets; scalar_t__ bytes; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  syncp; struct bcm_sysport_tx_ring* tx_rings; TYPE_1__* netdev; } ;
struct TYPE_2__ {unsigned int num_tx_queues; } ;

/* Variables and functions */
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void bcm_sysport_update_tx_stats(struct bcm_sysport_priv *priv,
					u64 *tx_bytes, u64 *tx_packets)
{
	struct bcm_sysport_tx_ring *ring;
	u64 bytes = 0, packets = 0;
	unsigned int start;
	unsigned int q;

	for (q = 0; q < priv->netdev->num_tx_queues; q++) {
		ring = &priv->tx_rings[q];
		do {
			start = u64_stats_fetch_begin_irq(&priv->syncp);
			bytes = ring->bytes;
			packets = ring->packets;
		} while (u64_stats_fetch_retry_irq(&priv->syncp, start));

		*tx_bytes += bytes;
		*tx_packets += packets;
	}
}