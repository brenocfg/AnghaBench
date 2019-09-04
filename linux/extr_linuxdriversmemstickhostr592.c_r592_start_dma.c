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
typedef  int /*<<< orphan*/  u32 ;
struct r592_device {int /*<<< orphan*/  irq_lock; TYPE_1__* req; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IRQ_ACK_MASK ; 
 int /*<<< orphan*/  DMA_IRQ_EN_MASK ; 
 int /*<<< orphan*/  R592_FIFO_DMA ; 
 int /*<<< orphan*/  R592_FIFO_DMA_SETTINGS ; 
 int /*<<< orphan*/  R592_FIFO_DMA_SETTINGS_DIR ; 
 int /*<<< orphan*/  R592_FIFO_DMA_SETTINGS_EN ; 
 int /*<<< orphan*/  R592_REG_MSC ; 
 int /*<<< orphan*/  r592_clear_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_set_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_write_reg (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void r592_start_dma(struct r592_device *dev, bool is_write)
{
	unsigned long flags;
	u32 reg;
	spin_lock_irqsave(&dev->irq_lock, flags);

	/* Ack interrupts (just in case) + enable them */
	r592_clear_reg_mask(dev, R592_REG_MSC, DMA_IRQ_ACK_MASK);
	r592_set_reg_mask(dev, R592_REG_MSC, DMA_IRQ_EN_MASK);

	/* Set DMA address */
	r592_write_reg(dev, R592_FIFO_DMA, sg_dma_address(&dev->req->sg));

	/* Enable the DMA */
	reg = r592_read_reg(dev, R592_FIFO_DMA_SETTINGS);
	reg |= R592_FIFO_DMA_SETTINGS_EN;

	if (!is_write)
		reg |= R592_FIFO_DMA_SETTINGS_DIR;
	else
		reg &= ~R592_FIFO_DMA_SETTINGS_DIR;
	r592_write_reg(dev, R592_FIFO_DMA_SETTINGS, reg);

	spin_unlock_irqrestore(&dev->irq_lock, flags);
}