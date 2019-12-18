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
struct enetc_rx_swbd {int /*<<< orphan*/ * page; int /*<<< orphan*/  dma; int /*<<< orphan*/  page_offset; } ;
struct enetc_bdr {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ENETC_RXB_DMA_SIZE ; 
 int /*<<< orphan*/  ENETC_RXB_TRUESIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_page_reusable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_reuse_page (struct enetc_bdr*,struct enetc_rx_swbd*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_ref_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enetc_put_rx_buff(struct enetc_bdr *rx_ring,
			      struct enetc_rx_swbd *rx_swbd)
{
	if (likely(enetc_page_reusable(rx_swbd->page))) {
		rx_swbd->page_offset ^= ENETC_RXB_TRUESIZE;
		page_ref_inc(rx_swbd->page);

		enetc_reuse_page(rx_ring, rx_swbd);

		/* sync for use by the device */
		dma_sync_single_range_for_device(rx_ring->dev, rx_swbd->dma,
						 rx_swbd->page_offset,
						 ENETC_RXB_DMA_SIZE,
						 DMA_FROM_DEVICE);
	} else {
		dma_unmap_page(rx_ring->dev, rx_swbd->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
	}

	rx_swbd->page = NULL;
}