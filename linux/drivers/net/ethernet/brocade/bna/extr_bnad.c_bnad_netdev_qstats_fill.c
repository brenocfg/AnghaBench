#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct bnad {int num_rx; int num_rxp_per_rx; int num_tx; int num_txq_per_tx; TYPE_8__* tx_info; TYPE_5__* rx_info; } ;
struct TYPE_16__ {TYPE_7__** tcb; } ;
struct TYPE_15__ {TYPE_6__* txq; } ;
struct TYPE_14__ {scalar_t__ tx_bytes; scalar_t__ tx_packets; } ;
struct TYPE_13__ {TYPE_4__* rx_ctrl; } ;
struct TYPE_12__ {TYPE_3__* ccb; } ;
struct TYPE_11__ {TYPE_2__** rcb; } ;
struct TYPE_10__ {TYPE_1__* rxq; } ;
struct TYPE_9__ {scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;

/* Variables and functions */

void
bnad_netdev_qstats_fill(struct bnad *bnad, struct rtnl_link_stats64 *stats)
{
	int i, j;

	for (i = 0; i < bnad->num_rx; i++) {
		for (j = 0; j < bnad->num_rxp_per_rx; j++) {
			if (bnad->rx_info[i].rx_ctrl[j].ccb) {
				stats->rx_packets += bnad->rx_info[i].
				rx_ctrl[j].ccb->rcb[0]->rxq->rx_packets;
				stats->rx_bytes += bnad->rx_info[i].
					rx_ctrl[j].ccb->rcb[0]->rxq->rx_bytes;
				if (bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
					bnad->rx_info[i].rx_ctrl[j].ccb->
					rcb[1]->rxq) {
					stats->rx_packets +=
						bnad->rx_info[i].rx_ctrl[j].
						ccb->rcb[1]->rxq->rx_packets;
					stats->rx_bytes +=
						bnad->rx_info[i].rx_ctrl[j].
						ccb->rcb[1]->rxq->rx_bytes;
				}
			}
		}
	}
	for (i = 0; i < bnad->num_tx; i++) {
		for (j = 0; j < bnad->num_txq_per_tx; j++) {
			if (bnad->tx_info[i].tcb[j]) {
				stats->tx_packets +=
				bnad->tx_info[i].tcb[j]->txq->tx_packets;
				stats->tx_bytes +=
					bnad->tx_info[i].tcb[j]->txq->tx_bytes;
			}
		}
	}
}