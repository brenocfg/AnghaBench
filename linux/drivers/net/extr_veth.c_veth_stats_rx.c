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
struct veth_rq_stats {scalar_t__ xdp_drops; scalar_t__ xdp_bytes; scalar_t__ xdp_packets; int /*<<< orphan*/  syncp; } ;
struct veth_priv {TYPE_1__* rq; } ;
struct net_device {int num_rx_queues; } ;
struct TYPE_2__ {struct veth_rq_stats stats; } ;

/* Variables and functions */
 struct veth_priv* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void veth_stats_rx(struct veth_rq_stats *result, struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);
	int i;

	result->xdp_packets = 0;
	result->xdp_bytes = 0;
	result->xdp_drops = 0;
	for (i = 0; i < dev->num_rx_queues; i++) {
		struct veth_rq_stats *stats = &priv->rq[i].stats;
		u64 packets, bytes, drops;
		unsigned int start;

		do {
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->xdp_packets;
			bytes = stats->xdp_bytes;
			drops = stats->xdp_drops;
		} while (u64_stats_fetch_retry_irq(&stats->syncp, start));
		result->xdp_packets += packets;
		result->xdp_bytes += bytes;
		result->xdp_drops += drops;
	}
}