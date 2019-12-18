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
struct enetc_rx_swbd {int /*<<< orphan*/ * page; int /*<<< orphan*/  dma; } ;
struct enetc_bdr {int bd_count; scalar_t__ next_to_alloc; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  dev; struct enetc_rx_swbd* rx_swbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_free_rx_ring(struct enetc_bdr *rx_ring)
{
	int i;

	if (!rx_ring->rx_swbd)
		return;

	for (i = 0; i < rx_ring->bd_count; i++) {
		struct enetc_rx_swbd *rx_swbd = &rx_ring->rx_swbd[i];

		if (!rx_swbd->page)
			continue;

		dma_unmap_page(rx_ring->dev, rx_swbd->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
		__free_page(rx_swbd->page);
		rx_swbd->page = NULL;
	}

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	rx_ring->next_to_alloc = 0;
}