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
struct enetc_tx_swbd {scalar_t__ dma; int /*<<< orphan*/  len; scalar_t__ is_dma_page; } ;
struct enetc_bdr {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_unmap_tx_buff(struct enetc_bdr *tx_ring,
				struct enetc_tx_swbd *tx_swbd)
{
	if (tx_swbd->is_dma_page)
		dma_unmap_page(tx_ring->dev, tx_swbd->dma,
			       tx_swbd->len, DMA_TO_DEVICE);
	else
		dma_unmap_single(tx_ring->dev, tx_swbd->dma,
				 tx_swbd->len, DMA_TO_DEVICE);
	tx_swbd->dma = 0;
}