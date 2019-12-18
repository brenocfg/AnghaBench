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
typedef  size_t u16 ;
struct gfar_rx_buff {int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; } ;
struct gfar_priv_rx_q {size_t next_to_alloc; size_t rx_ring_size; int /*<<< orphan*/  dev; struct gfar_rx_buff* rx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFAR_RXB_TRUESIZE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfar_reuse_rx_page(struct gfar_priv_rx_q *rxq,
			       struct gfar_rx_buff *old_rxb)
{
	struct gfar_rx_buff *new_rxb;
	u16 nta = rxq->next_to_alloc;

	new_rxb = &rxq->rx_buff[nta];

	/* find next buf that can reuse a page */
	nta++;
	rxq->next_to_alloc = (nta < rxq->rx_ring_size) ? nta : 0;

	/* copy page reference */
	*new_rxb = *old_rxb;

	/* sync for use by the device */
	dma_sync_single_range_for_device(rxq->dev, old_rxb->dma,
					 old_rxb->page_offset,
					 GFAR_RXB_TRUESIZE, DMA_FROM_DEVICE);
}