#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct netdev_queue {int dummy; } ;
struct mvneta_tx_queue {int txq_get_index; struct sk_buff** tx_skb; struct mvneta_tx_desc* descs; } ;
struct mvneta_tx_desc {int /*<<< orphan*/  data_size; int /*<<< orphan*/  buf_phys_addr; } ;
struct mvneta_port {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IS_TSO_HEADER (struct mvneta_tx_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_txq_inc_get (struct mvneta_tx_queue*) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,unsigned int,unsigned int) ; 

__attribute__((used)) static void mvneta_txq_bufs_free(struct mvneta_port *pp,
				 struct mvneta_tx_queue *txq, int num,
				 struct netdev_queue *nq)
{
	unsigned int bytes_compl = 0, pkts_compl = 0;
	int i;

	for (i = 0; i < num; i++) {
		struct mvneta_tx_desc *tx_desc = txq->descs +
			txq->txq_get_index;
		struct sk_buff *skb = txq->tx_skb[txq->txq_get_index];

		if (skb) {
			bytes_compl += skb->len;
			pkts_compl++;
		}

		mvneta_txq_inc_get(txq);

		if (!IS_TSO_HEADER(txq, tx_desc->buf_phys_addr))
			dma_unmap_single(pp->dev->dev.parent,
					 tx_desc->buf_phys_addr,
					 tx_desc->data_size, DMA_TO_DEVICE);
		if (!skb)
			continue;
		dev_kfree_skb_any(skb);
	}

	netdev_tx_completed_queue(nq, pkts_compl, bytes_compl);
}