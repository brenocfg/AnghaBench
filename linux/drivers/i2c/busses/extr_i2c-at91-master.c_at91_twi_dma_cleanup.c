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
struct at91_twi_dma {int xfer_in_progress; scalar_t__ direction; int buf_mapped; int /*<<< orphan*/ * sg; int /*<<< orphan*/  chan_tx; int /*<<< orphan*/  chan_rx; } ;
struct at91_twi_dev {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  dev; struct at91_twi_dma dma; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  at91_twi_irq_restore (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_irq_save (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void at91_twi_dma_cleanup(struct at91_twi_dev *dev)
{
	struct at91_twi_dma *dma = &dev->dma;

	at91_twi_irq_save(dev);

	if (dma->xfer_in_progress) {
		if (dma->direction == DMA_FROM_DEVICE)
			dmaengine_terminate_all(dma->chan_rx);
		else
			dmaengine_terminate_all(dma->chan_tx);
		dma->xfer_in_progress = false;
	}
	if (dma->buf_mapped) {
		dma_unmap_single(dev->dev, sg_dma_address(&dma->sg[0]),
				 dev->buf_len, dma->direction);
		dma->buf_mapped = false;
	}

	at91_twi_irq_restore(dev);
}