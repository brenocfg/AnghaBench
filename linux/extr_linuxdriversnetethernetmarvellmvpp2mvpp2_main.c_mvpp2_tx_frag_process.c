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
struct sk_buff {int dummy; } ;
struct mvpp2_txq_pcpu {int dummy; } ;
struct mvpp2_tx_queue {struct mvpp2_tx_desc* descs; int /*<<< orphan*/  id; int /*<<< orphan*/  pcpu; } ;
struct mvpp2_tx_desc {int dummy; } ;
struct mvpp2_port {TYPE_3__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  p; } ;
struct TYPE_9__ {int page_offset; int /*<<< orphan*/  size; TYPE_1__ page; } ;
typedef  TYPE_4__ skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_10__ {int nr_frags; TYPE_4__* frags; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MVPP2_TXD_L_DESC ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_cmd_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_dma_addr_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_size_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_txq_set (struct mvpp2_port*,struct mvpp2_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txq_desc_put (struct mvpp2_tx_queue*) ; 
 int /*<<< orphan*/  mvpp2_txq_inc_put (struct mvpp2_port*,struct mvpp2_txq_pcpu*,struct sk_buff*,struct mvpp2_tx_desc*) ; 
 struct mvpp2_tx_desc* mvpp2_txq_next_desc_get (struct mvpp2_tx_queue*) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 struct mvpp2_txq_pcpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_desc_unmap_put (struct mvpp2_port*,struct mvpp2_tx_queue*,struct mvpp2_tx_desc*) ; 

__attribute__((used)) static int mvpp2_tx_frag_process(struct mvpp2_port *port, struct sk_buff *skb,
				 struct mvpp2_tx_queue *aggr_txq,
				 struct mvpp2_tx_queue *txq)
{
	struct mvpp2_txq_pcpu *txq_pcpu = this_cpu_ptr(txq->pcpu);
	struct mvpp2_tx_desc *tx_desc;
	int i;
	dma_addr_t buf_dma_addr;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		void *addr = page_address(frag->page.p) + frag->page_offset;

		tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
		mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
		mvpp2_txdesc_size_set(port, tx_desc, frag->size);

		buf_dma_addr = dma_map_single(port->dev->dev.parent, addr,
					      frag->size, DMA_TO_DEVICE);
		if (dma_mapping_error(port->dev->dev.parent, buf_dma_addr)) {
			mvpp2_txq_desc_put(txq);
			goto cleanup;
		}

		mvpp2_txdesc_dma_addr_set(port, tx_desc, buf_dma_addr);

		if (i == (skb_shinfo(skb)->nr_frags - 1)) {
			/* Last descriptor */
			mvpp2_txdesc_cmd_set(port, tx_desc,
					     MVPP2_TXD_L_DESC);
			mvpp2_txq_inc_put(port, txq_pcpu, skb, tx_desc);
		} else {
			/* Descriptor in the middle: Not First, Not Last */
			mvpp2_txdesc_cmd_set(port, tx_desc, 0);
			mvpp2_txq_inc_put(port, txq_pcpu, NULL, tx_desc);
		}
	}

	return 0;
cleanup:
	/* Release all descriptors that were used to map fragments of
	 * this packet, as well as the corresponding DMA mappings
	 */
	for (i = i - 1; i >= 0; i--) {
		tx_desc = txq->descs + i;
		tx_desc_unmap_put(port, txq, tx_desc);
	}

	return -ENOMEM;
}