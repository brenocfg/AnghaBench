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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_6__ {scalar_t__ tx_dropped; scalar_t__ tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct qeth_qdio_out_q {TYPE_3__ stats; } ;
struct TYPE_5__ {unsigned int no_out_queues; struct qeth_qdio_out_q** out_qs; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct qeth_card {TYPE_2__ qdio; TYPE_1__ stats; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

void qeth_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct qeth_card *card = dev->ml_priv;
	struct qeth_qdio_out_q *queue;
	unsigned int i;

	QETH_CARD_TEXT(card, 5, "getstat");

	stats->rx_packets = card->stats.rx_packets;
	stats->rx_bytes = card->stats.rx_bytes;
	stats->rx_errors = card->stats.rx_errors;
	stats->rx_dropped = card->stats.rx_dropped;
	stats->multicast = card->stats.rx_multicast;

	for (i = 0; i < card->qdio.no_out_queues; i++) {
		queue = card->qdio.out_qs[i];

		stats->tx_packets += queue->stats.tx_packets;
		stats->tx_bytes += queue->stats.tx_bytes;
		stats->tx_errors += queue->stats.tx_errors;
		stats->tx_dropped += queue->stats.tx_dropped;
	}
}