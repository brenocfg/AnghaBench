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
struct virtnet_info {int max_queue_pairs; struct send_queue* sq; struct receive_queue* rq; } ;
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ packets; int /*<<< orphan*/  syncp; } ;
struct send_queue {TYPE_1__ stats; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_5__ {scalar_t__ drops; scalar_t__ bytes; scalar_t__ packets; int /*<<< orphan*/  syncp; } ;
struct receive_queue {TYPE_2__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;

/* Variables and functions */
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void virtnet_stats(struct net_device *dev,
			  struct rtnl_link_stats64 *tot)
{
	struct virtnet_info *vi = netdev_priv(dev);
	unsigned int start;
	int i;

	for (i = 0; i < vi->max_queue_pairs; i++) {
		u64 tpackets, tbytes, rpackets, rbytes, rdrops;
		struct receive_queue *rq = &vi->rq[i];
		struct send_queue *sq = &vi->sq[i];

		do {
			start = u64_stats_fetch_begin_irq(&sq->stats.syncp);
			tpackets = sq->stats.packets;
			tbytes   = sq->stats.bytes;
		} while (u64_stats_fetch_retry_irq(&sq->stats.syncp, start));

		do {
			start = u64_stats_fetch_begin_irq(&rq->stats.syncp);
			rpackets = rq->stats.packets;
			rbytes   = rq->stats.bytes;
			rdrops   = rq->stats.drops;
		} while (u64_stats_fetch_retry_irq(&rq->stats.syncp, start));

		tot->rx_packets += rpackets;
		tot->tx_packets += tpackets;
		tot->rx_bytes   += rbytes;
		tot->tx_bytes   += tbytes;
		tot->rx_dropped += rdrops;
	}

	tot->tx_dropped = dev->stats.tx_dropped;
	tot->tx_fifo_errors = dev->stats.tx_fifo_errors;
	tot->rx_length_errors = dev->stats.rx_length_errors;
	tot->rx_frame_errors = dev->stats.rx_frame_errors;
}