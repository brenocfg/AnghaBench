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
typedef  size_t u32 ;
struct ena_tx_buffer {int num_of_bufs; int /*<<< orphan*/  skb; struct ena_com_buf* bufs; } ;
struct ena_ring {size_t ring_size; int /*<<< orphan*/  qid; int /*<<< orphan*/  netdev; int /*<<< orphan*/  dev; struct ena_tx_buffer* tx_buffer_info; } ;
struct ena_com_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_notice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_free_tx_bufs(struct ena_ring *tx_ring)
{
	bool print_once = true;
	u32 i;

	for (i = 0; i < tx_ring->ring_size; i++) {
		struct ena_tx_buffer *tx_info = &tx_ring->tx_buffer_info[i];
		struct ena_com_buf *ena_buf;
		int nr_frags;
		int j;

		if (!tx_info->skb)
			continue;

		if (print_once) {
			netdev_notice(tx_ring->netdev,
				      "free uncompleted tx skb qid %d idx 0x%x\n",
				      tx_ring->qid, i);
			print_once = false;
		} else {
			netdev_dbg(tx_ring->netdev,
				   "free uncompleted tx skb qid %d idx 0x%x\n",
				   tx_ring->qid, i);
		}

		ena_buf = tx_info->bufs;
		dma_unmap_single(tx_ring->dev,
				 ena_buf->paddr,
				 ena_buf->len,
				 DMA_TO_DEVICE);

		/* unmap remaining mapped pages */
		nr_frags = tx_info->num_of_bufs - 1;
		for (j = 0; j < nr_frags; j++) {
			ena_buf++;
			dma_unmap_page(tx_ring->dev,
				       ena_buf->paddr,
				       ena_buf->len,
				       DMA_TO_DEVICE);
		}

		dev_kfree_skb_any(tx_info->skb);
	}
	netdev_tx_reset_queue(netdev_get_tx_queue(tx_ring->netdev,
						  tx_ring->qid));
}