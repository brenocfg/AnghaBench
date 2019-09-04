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
typedef  int uint32_t ;
struct jz4740_dma_dev {int /*<<< orphan*/ * chan; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int JZ_DMA_STATUS_CTRL_ENABLE ; 
 int JZ_DMA_STATUS_CTRL_TRANSFER_DONE ; 
 scalar_t__ JZ_REG_DMA_IRQ ; 
 int /*<<< orphan*/  JZ_REG_DMA_STATUS_CTRL (unsigned int) ; 
 int /*<<< orphan*/  jz4740_dma_chan_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4740_dma_write_mask (struct jz4740_dma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t jz4740_dma_irq(int irq, void *devid)
{
	struct jz4740_dma_dev *dmadev = devid;
	uint32_t irq_status;
	unsigned int i;

	irq_status = readl(dmadev->base + JZ_REG_DMA_IRQ);

	for (i = 0; i < 6; ++i) {
		if (irq_status & (1 << i)) {
			jz4740_dma_write_mask(dmadev,
				JZ_REG_DMA_STATUS_CTRL(i), 0,
				JZ_DMA_STATUS_CTRL_ENABLE |
				JZ_DMA_STATUS_CTRL_TRANSFER_DONE);

			jz4740_dma_chan_irq(&dmadev->chan[i]);
		}
	}

	return IRQ_HANDLED;
}