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
struct net_device {int dummy; } ;
struct fec_enet_private {int num_tx_queues; int num_rx_queues; TYPE_4__** rx_queue; int /*<<< orphan*/  total_rx_ring_size; TYPE_1__* pdev; struct fec_enet_priv_tx_q** tx_queue; int /*<<< orphan*/  total_tx_ring_size; } ;
struct TYPE_6__ {int ring_size; } ;
struct fec_enet_priv_tx_q {int tx_stop_threshold; int tx_wake_threshold; int /*<<< orphan*/  tso_hdrs; int /*<<< orphan*/  tso_hdrs_dma; TYPE_2__ bd; } ;
struct TYPE_7__ {scalar_t__ ring_size; } ;
struct TYPE_8__ {TYPE_3__ bd; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FEC_MAX_SKB_DESCS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RX_RING_SIZE ; 
 int TSO_HEADER_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec_enet_free_queue (struct net_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fec_enet_alloc_queue(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int i;
	int ret = 0;
	struct fec_enet_priv_tx_q *txq;

	for (i = 0; i < fep->num_tx_queues; i++) {
		txq = kzalloc(sizeof(*txq), GFP_KERNEL);
		if (!txq) {
			ret = -ENOMEM;
			goto alloc_failed;
		}

		fep->tx_queue[i] = txq;
		txq->bd.ring_size = TX_RING_SIZE;
		fep->total_tx_ring_size += fep->tx_queue[i]->bd.ring_size;

		txq->tx_stop_threshold = FEC_MAX_SKB_DESCS;
		txq->tx_wake_threshold =
			(txq->bd.ring_size - txq->tx_stop_threshold) / 2;

		txq->tso_hdrs = dma_alloc_coherent(&fep->pdev->dev,
					txq->bd.ring_size * TSO_HEADER_SIZE,
					&txq->tso_hdrs_dma,
					GFP_KERNEL);
		if (!txq->tso_hdrs) {
			ret = -ENOMEM;
			goto alloc_failed;
		}
	}

	for (i = 0; i < fep->num_rx_queues; i++) {
		fep->rx_queue[i] = kzalloc(sizeof(*fep->rx_queue[i]),
					   GFP_KERNEL);
		if (!fep->rx_queue[i]) {
			ret = -ENOMEM;
			goto alloc_failed;
		}

		fep->rx_queue[i]->bd.ring_size = RX_RING_SIZE;
		fep->total_rx_ring_size += fep->rx_queue[i]->bd.ring_size;
	}
	return ret;

alloc_failed:
	fec_enet_free_queue(ndev);
	return ret;
}