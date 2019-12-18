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
typedef  int u32 ;
typedef  int u16 ;
struct r592_device {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  dma_done; int /*<<< orphan*/  detect_timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  R592_REG_MSC ; 
 int R592_REG_MSC_FIFO_DMA_DONE ; 
 int R592_REG_MSC_FIFO_DMA_ERR ; 
 int R592_REG_MSC_IRQ_INSERT ; 
 int R592_REG_MSC_IRQ_REMOVE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  message (char*,...) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_stop_dma (struct r592_device*,int) ; 
 int /*<<< orphan*/  r592_write_reg (struct r592_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t r592_irq(int irq, void *data)
{
	struct r592_device *dev = (struct r592_device *)data;
	irqreturn_t ret = IRQ_NONE;
	u32 reg;
	u16 irq_enable, irq_status;
	unsigned long flags;
	int error;

	spin_lock_irqsave(&dev->irq_lock, flags);

	reg = r592_read_reg(dev, R592_REG_MSC);
	irq_enable = reg >> 16;
	irq_status = reg & 0xFFFF;

	/* Ack the interrupts */
	reg &= ~irq_status;
	r592_write_reg(dev, R592_REG_MSC, reg);

	/* Get the IRQ status minus bits that aren't enabled */
	irq_status &= (irq_enable);

	/* Due to limitation of memstick core, we don't look at bits that
		indicate that card was removed/inserted and/or present */
	if (irq_status & (R592_REG_MSC_IRQ_INSERT | R592_REG_MSC_IRQ_REMOVE)) {

		bool card_was_added = irq_status & R592_REG_MSC_IRQ_INSERT;
		ret = IRQ_HANDLED;

		message("IRQ: card %s", card_was_added ? "added" : "removed");

		mod_timer(&dev->detect_timer,
			jiffies + msecs_to_jiffies(card_was_added ? 500 : 50));
	}

	if (irq_status &
		(R592_REG_MSC_FIFO_DMA_DONE | R592_REG_MSC_FIFO_DMA_ERR)) {
		ret = IRQ_HANDLED;

		if (irq_status & R592_REG_MSC_FIFO_DMA_ERR) {
			message("IRQ: DMA error");
			error = -EIO;
		} else {
			dbg_verbose("IRQ: dma done");
			error = 0;
		}

		r592_stop_dma(dev, error);
		complete(&dev->dma_done);
	}

	spin_unlock_irqrestore(&dev->irq_lock, flags);
	return ret;
}