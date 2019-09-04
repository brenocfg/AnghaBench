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
struct xgene_dma_chan {int /*<<< orphan*/  rx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_dma_cleanup_descriptors (struct xgene_dma_chan*) ; 

__attribute__((used)) static void xgene_dma_tasklet_cb(unsigned long data)
{
	struct xgene_dma_chan *chan = (struct xgene_dma_chan *)data;

	/* Run all cleanup for descriptors which have been completed */
	xgene_dma_cleanup_descriptors(chan);

	/* Re-enable DMA channel IRQ */
	enable_irq(chan->rx_irq);
}