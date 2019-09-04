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
typedef  scalar_t__ u16 ;
struct alx_rx_queue {scalar_t__ count; scalar_t__ rrd_read_idx; scalar_t__ read_idx; scalar_t__ write_idx; int /*<<< orphan*/  dev; struct alx_buffer* bufs; } ;
struct alx_buffer {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct alx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct alx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct alx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct alx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size ; 

__attribute__((used)) static void alx_free_rxring_buf(struct alx_rx_queue *rxq)
{
	struct alx_buffer *cur_buf;
	u16 i;

	if (!rxq->bufs)
		return;

	for (i = 0; i < rxq->count; i++) {
		cur_buf = rxq->bufs + i;
		if (cur_buf->skb) {
			dma_unmap_single(rxq->dev,
					 dma_unmap_addr(cur_buf, dma),
					 dma_unmap_len(cur_buf, size),
					 DMA_FROM_DEVICE);
			dev_kfree_skb(cur_buf->skb);
			cur_buf->skb = NULL;
			dma_unmap_len_set(cur_buf, size, 0);
			dma_unmap_addr_set(cur_buf, dma, 0);
		}
	}

	rxq->write_idx = 0;
	rxq->read_idx = 0;
	rxq->rrd_read_idx = 0;
}