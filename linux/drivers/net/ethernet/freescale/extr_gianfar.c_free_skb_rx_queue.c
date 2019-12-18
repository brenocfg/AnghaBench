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
struct rxbd8 {scalar_t__ bufPtr; scalar_t__ lstatus; } ;
struct gfar_rx_buff {int /*<<< orphan*/ * page; int /*<<< orphan*/  dma; } ;
struct gfar_priv_rx_q {int rx_ring_size; struct gfar_rx_buff* rx_buff; int /*<<< orphan*/  dev; int /*<<< orphan*/  skb; struct rxbd8* rx_bd_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gfar_rx_buff*) ; 

__attribute__((used)) static void free_skb_rx_queue(struct gfar_priv_rx_q *rx_queue)
{
	int i;

	struct rxbd8 *rxbdp = rx_queue->rx_bd_base;

	dev_kfree_skb(rx_queue->skb);

	for (i = 0; i < rx_queue->rx_ring_size; i++) {
		struct	gfar_rx_buff *rxb = &rx_queue->rx_buff[i];

		rxbdp->lstatus = 0;
		rxbdp->bufPtr = 0;
		rxbdp++;

		if (!rxb->page)
			continue;

		dma_unmap_page(rx_queue->dev, rxb->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
		__free_page(rxb->page);

		rxb->page = NULL;
	}

	kfree(rx_queue->rx_buff);
	rx_queue->rx_buff = NULL;
}