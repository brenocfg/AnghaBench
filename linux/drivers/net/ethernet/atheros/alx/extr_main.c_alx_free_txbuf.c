#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct alx_tx_queue {int /*<<< orphan*/  dev; struct alx_buffer* bufs; } ;
struct alx_buffer {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct alx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct alx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct alx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size ; 

__attribute__((used)) static void alx_free_txbuf(struct alx_tx_queue *txq, int entry)
{
	struct alx_buffer *txb = &txq->bufs[entry];

	if (dma_unmap_len(txb, size)) {
		dma_unmap_single(txq->dev,
				 dma_unmap_addr(txb, dma),
				 dma_unmap_len(txb, size),
				 DMA_TO_DEVICE);
		dma_unmap_len_set(txb, size, 0);
	}

	if (txb->skb) {
		dev_kfree_skb_any(txb->skb);
		txb->skb = NULL;
	}
}