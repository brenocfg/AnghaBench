#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct myri10ge_tx_buf {int done; int req; int mask; int /*<<< orphan*/ * req_list; TYPE_4__* req_bytes; TYPE_4__* info; } ;
struct TYPE_11__ {int fill_cnt; int cnt; int mask; TYPE_4__* shadow; TYPE_4__* info; } ;
struct TYPE_10__ {int cnt; int fill_cnt; int mask; TYPE_4__* shadow; TYPE_4__* info; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_dropped; } ;
struct myri10ge_slice_state {struct myri10ge_tx_buf tx; TYPE_3__ rx_small; TYPE_2__ rx_big; TYPE_1__ stats; struct myri10ge_priv* mgp; } ;
struct myri10ge_priv {scalar_t__ big_bytes; scalar_t__ small_bytes; int /*<<< orphan*/  pdev; } ;
struct TYPE_12__ {struct sk_buff* skb; int /*<<< orphan*/  page; void* page_offset; } ;

/* Variables and functions */
 scalar_t__ MXGEFW_PAD ; 
 void* MYRI10GE_ALLOC_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  bus ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int dma_unmap_len (TYPE_4__*,int) ; 
 int /*<<< orphan*/  dma_unmap_len_set (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  myri10ge_unmap_rx_page (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myri10ge_free_rings(struct myri10ge_slice_state *ss)
{
	struct myri10ge_priv *mgp = ss->mgp;
	struct sk_buff *skb;
	struct myri10ge_tx_buf *tx;
	int i, len, idx;

	/* If not allocated, skip it */
	if (ss->tx.req_list == NULL)
		return;

	for (i = ss->rx_big.cnt; i < ss->rx_big.fill_cnt; i++) {
		idx = i & ss->rx_big.mask;
		if (i == ss->rx_big.fill_cnt - 1)
			ss->rx_big.info[idx].page_offset = MYRI10GE_ALLOC_SIZE;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_big.info[idx],
				       mgp->big_bytes);
		put_page(ss->rx_big.info[idx].page);
	}

	if (mgp->small_bytes == 0)
		ss->rx_small.fill_cnt = ss->rx_small.cnt;
	for (i = ss->rx_small.cnt; i < ss->rx_small.fill_cnt; i++) {
		idx = i & ss->rx_small.mask;
		if (i == ss->rx_small.fill_cnt - 1)
			ss->rx_small.info[idx].page_offset =
			    MYRI10GE_ALLOC_SIZE;
		myri10ge_unmap_rx_page(mgp->pdev, &ss->rx_small.info[idx],
				       mgp->small_bytes + MXGEFW_PAD);
		put_page(ss->rx_small.info[idx].page);
	}
	tx = &ss->tx;
	while (tx->done != tx->req) {
		idx = tx->done & tx->mask;
		skb = tx->info[idx].skb;

		/* Mark as free */
		tx->info[idx].skb = NULL;
		tx->done++;
		len = dma_unmap_len(&tx->info[idx], len);
		dma_unmap_len_set(&tx->info[idx], len, 0);
		if (skb) {
			ss->stats.tx_dropped++;
			dev_kfree_skb_any(skb);
			if (len)
				pci_unmap_single(mgp->pdev,
						 dma_unmap_addr(&tx->info[idx],
								bus), len,
						 PCI_DMA_TODEVICE);
		} else {
			if (len)
				pci_unmap_page(mgp->pdev,
					       dma_unmap_addr(&tx->info[idx],
							      bus), len,
					       PCI_DMA_TODEVICE);
		}
	}
	kfree(ss->rx_big.info);

	kfree(ss->rx_small.info);

	kfree(ss->tx.info);

	kfree(ss->rx_big.shadow);

	kfree(ss->rx_small.shadow);

	kfree(ss->tx.req_bytes);
	ss->tx.req_bytes = NULL;
	ss->tx.req_list = NULL;
}