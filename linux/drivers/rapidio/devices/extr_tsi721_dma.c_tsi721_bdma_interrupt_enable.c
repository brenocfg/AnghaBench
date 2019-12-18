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
struct tsi721_bdma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TSI721_DMAC_INT ; 
 scalar_t__ TSI721_DMAC_INTE ; 
 int /*<<< orphan*/  TSI721_DMAC_INT_ALL ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
tsi721_bdma_interrupt_enable(struct tsi721_bdma_chan *bdma_chan, int enable)
{
	if (enable) {
		/* Clear pending BDMA channel interrupts */
		iowrite32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INT);
		ioread32(bdma_chan->regs + TSI721_DMAC_INT);
		/* Enable BDMA channel interrupts */
		iowrite32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INTE);
	} else {
		/* Disable BDMA channel interrupts */
		iowrite32(0, bdma_chan->regs + TSI721_DMAC_INTE);
		/* Clear pending BDMA channel interrupts */
		iowrite32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INT);
	}

}