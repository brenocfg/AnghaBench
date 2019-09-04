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
struct jz4780_dma_dev {int /*<<< orphan*/ * chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int JZ_DMA_DMAC_AR ; 
 int JZ_DMA_DMAC_HLT ; 
 int JZ_DMA_NR_CHANNELS ; 
 int /*<<< orphan*/  JZ_DMA_REG_DIRQP ; 
 int /*<<< orphan*/  JZ_DMA_REG_DMAC ; 
 int /*<<< orphan*/  jz4780_dma_chan_irq (struct jz4780_dma_dev*,int /*<<< orphan*/ *) ; 
 int jz4780_dma_readl (struct jz4780_dma_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_dma_writel (struct jz4780_dma_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t jz4780_dma_irq_handler(int irq, void *data)
{
	struct jz4780_dma_dev *jzdma = data;
	uint32_t pending, dmac;
	int i;

	pending = jz4780_dma_readl(jzdma, JZ_DMA_REG_DIRQP);

	for (i = 0; i < JZ_DMA_NR_CHANNELS; i++) {
		if (!(pending & (1<<i)))
			continue;

		jz4780_dma_chan_irq(jzdma, &jzdma->chan[i]);
	}

	/* Clear halt and address error status of all channels. */
	dmac = jz4780_dma_readl(jzdma, JZ_DMA_REG_DMAC);
	dmac &= ~(JZ_DMA_DMAC_HLT | JZ_DMA_DMAC_AR);
	jz4780_dma_writel(jzdma, JZ_DMA_REG_DMAC, dmac);

	/* Clear interrupt pending status. */
	jz4780_dma_writel(jzdma, JZ_DMA_REG_DIRQP, 0);

	return IRQ_HANDLED;
}