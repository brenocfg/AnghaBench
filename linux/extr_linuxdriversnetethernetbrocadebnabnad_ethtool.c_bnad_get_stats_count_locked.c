#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bnad {int num_rx; int num_rxp_per_rx; int num_tx; int num_txq_per_tx; TYPE_5__* tx_info; TYPE_4__* rx_info; int /*<<< orphan*/  bna; } ;
struct TYPE_10__ {int /*<<< orphan*/  tx; } ;
struct TYPE_9__ {TYPE_3__* rx_ctrl; int /*<<< orphan*/  rx; } ;
struct TYPE_8__ {TYPE_2__* ccb; } ;
struct TYPE_7__ {TYPE_1__** rcb; } ;
struct TYPE_6__ {scalar_t__ rxq; } ;

/* Variables and functions */
 int BNAD_ETHTOOL_STATS_NUM ; 
 int BNAD_NUM_CQ_COUNTERS ; 
 int BNAD_NUM_RXF_COUNTERS ; 
 int BNAD_NUM_RXQ_COUNTERS ; 
 int BNAD_NUM_TXF_COUNTERS ; 
 int BNAD_NUM_TXQ_COUNTERS ; 
 int bna_rx_rid_mask (int /*<<< orphan*/ *) ; 
 int bna_tx_rid_mask (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnad_get_stats_count_locked(struct net_device *netdev)
{
	struct bnad *bnad = netdev_priv(netdev);
	int i, j, count = 0, rxf_active_num = 0, txf_active_num = 0;
	u32 bmap;

	bmap = bna_tx_rid_mask(&bnad->bna);
	for (i = 0; bmap; i++) {
		if (bmap & 1)
			txf_active_num++;
		bmap >>= 1;
	}
	bmap = bna_rx_rid_mask(&bnad->bna);
	for (i = 0; bmap; i++) {
		if (bmap & 1)
			rxf_active_num++;
		bmap >>= 1;
	}
	count = BNAD_ETHTOOL_STATS_NUM +
		txf_active_num * BNAD_NUM_TXF_COUNTERS +
		rxf_active_num * BNAD_NUM_RXF_COUNTERS;

	for (i = 0; i < bnad->num_rx; i++) {
		if (!bnad->rx_info[i].rx)
			continue;
		count += bnad->num_rxp_per_rx * BNAD_NUM_CQ_COUNTERS;
		count += bnad->num_rxp_per_rx * BNAD_NUM_RXQ_COUNTERS;
		for (j = 0; j < bnad->num_rxp_per_rx; j++)
			if (bnad->rx_info[i].rx_ctrl[j].ccb &&
				bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
				bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1]->rxq)
				count +=  BNAD_NUM_RXQ_COUNTERS;
	}

	for (i = 0; i < bnad->num_tx; i++) {
		if (!bnad->tx_info[i].tx)
			continue;
		count += bnad->num_txq_per_tx * BNAD_NUM_TXQ_COUNTERS;
	}
	return count;
}