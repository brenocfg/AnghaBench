#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int consume_idx; scalar_t__ count; } ;
struct emac_tx_queue {int consume_mask; int consume_shift; TYPE_2__ tpd; scalar_t__ consume_reg; } ;
struct emac_buffer {TYPE_6__* skb; scalar_t__ dma_addr; int /*<<< orphan*/  length; } ;
struct emac_adapter {TYPE_3__* netdev; scalar_t__ base; } ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct emac_buffer* GET_TPD_BUFFER (struct emac_tx_queue*,int) ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  dev_consume_skb_irq (TYPE_6__*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emac_tpd_num_free_descs (struct emac_tx_queue*) ; 
 int /*<<< orphan*/  netdev_completed_queue (TYPE_3__*,int,int) ; 
 scalar_t__ netif_queue_stopped (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 
 int readl_relaxed (scalar_t__) ; 

void emac_mac_tx_process(struct emac_adapter *adpt, struct emac_tx_queue *tx_q)
{
	u32 reg = readl_relaxed(adpt->base + tx_q->consume_reg);
	u32 hw_consume_idx, pkts_compl = 0, bytes_compl = 0;
	struct emac_buffer *tpbuf;

	hw_consume_idx = (reg & tx_q->consume_mask) >> tx_q->consume_shift;

	while (tx_q->tpd.consume_idx != hw_consume_idx) {
		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.consume_idx);
		if (tpbuf->dma_addr) {
			dma_unmap_page(adpt->netdev->dev.parent,
				       tpbuf->dma_addr, tpbuf->length,
				       DMA_TO_DEVICE);
			tpbuf->dma_addr = 0;
		}

		if (tpbuf->skb) {
			pkts_compl++;
			bytes_compl += tpbuf->skb->len;
			dev_consume_skb_irq(tpbuf->skb);
			tpbuf->skb = NULL;
		}

		if (++tx_q->tpd.consume_idx == tx_q->tpd.count)
			tx_q->tpd.consume_idx = 0;
	}

	netdev_completed_queue(adpt->netdev, pkts_compl, bytes_compl);

	if (netif_queue_stopped(adpt->netdev))
		if (emac_tpd_num_free_descs(tx_q) > (MAX_SKB_FRAGS + 1))
			netif_wake_queue(adpt->netdev);
}