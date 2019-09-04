#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ep93xx_dma_desc {int complete; } ;
struct ep93xx_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  flags; TYPE_1__* edma; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int (* hw_interrupt ) (struct ep93xx_dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_DMA_IS_CYCLIC ; 
#define  INTERRUPT_DONE 129 
#define  INTERRUPT_NEXT_BUFFER 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  chan2dev (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct ep93xx_dma_desc* ep93xx_dma_get_active (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ep93xx_dma_interrupt(int irq, void *dev_id)
{
	struct ep93xx_dma_chan *edmac = dev_id;
	struct ep93xx_dma_desc *desc;
	irqreturn_t ret = IRQ_HANDLED;

	spin_lock(&edmac->lock);

	desc = ep93xx_dma_get_active(edmac);
	if (!desc) {
		dev_warn(chan2dev(edmac),
			 "got interrupt while active list is empty\n");
		spin_unlock(&edmac->lock);
		return IRQ_NONE;
	}

	switch (edmac->edma->hw_interrupt(edmac)) {
	case INTERRUPT_DONE:
		desc->complete = true;
		tasklet_schedule(&edmac->tasklet);
		break;

	case INTERRUPT_NEXT_BUFFER:
		if (test_bit(EP93XX_DMA_IS_CYCLIC, &edmac->flags))
			tasklet_schedule(&edmac->tasklet);
		break;

	default:
		dev_warn(chan2dev(edmac), "unknown interrupt!\n");
		ret = IRQ_NONE;
		break;
	}

	spin_unlock(&edmac->lock);
	return ret;
}