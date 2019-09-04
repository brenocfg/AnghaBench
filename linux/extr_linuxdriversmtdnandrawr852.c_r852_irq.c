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
typedef  int uint8_t ;
struct r852_device {int card_detected; int card_unstable; int dma_stage; scalar_t__ dma_state; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dma_done; int /*<<< orphan*/  card_detect_work; int /*<<< orphan*/  card_workqueue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DMA_INTERNAL ; 
 scalar_t__ DMA_MEMORY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int R852_CARD_IRQ_INSERT ; 
 int R852_CARD_IRQ_REMOVE ; 
 int /*<<< orphan*/  R852_CARD_IRQ_STA ; 
 int R852_CARD_STA_CD ; 
 int R852_DMA_IRQ_ERROR ; 
 int R852_DMA_IRQ_INTERNAL ; 
 int R852_DMA_IRQ_MASK ; 
 int R852_DMA_IRQ_MEMORY ; 
 int /*<<< orphan*/  R852_DMA_IRQ_STA ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_disable_irqs (struct r852_device*) ; 
 int /*<<< orphan*/  r852_dma_done (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_dma_enable (struct r852_device*) ; 
 int r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 
 int r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg (struct r852_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r852_write_reg_dword (struct r852_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t r852_irq(int irq, void *data)
{
	struct r852_device *dev = (struct r852_device *)data;

	uint8_t card_status, dma_status;
	unsigned long flags;
	irqreturn_t ret = IRQ_NONE;

	spin_lock_irqsave(&dev->irqlock, flags);

	/* handle card detection interrupts first */
	card_status = r852_read_reg(dev, R852_CARD_IRQ_STA);
	r852_write_reg(dev, R852_CARD_IRQ_STA, card_status);

	if (card_status & (R852_CARD_IRQ_INSERT|R852_CARD_IRQ_REMOVE)) {

		ret = IRQ_HANDLED;
		dev->card_detected = !!(card_status & R852_CARD_IRQ_INSERT);

		/* we shouldn't receive any interrupts if we wait for card
			to settle */
		WARN_ON(dev->card_unstable);

		/* disable irqs while card is unstable */
		/* this will timeout DMA if active, but better that garbage */
		r852_disable_irqs(dev);

		if (dev->card_unstable)
			goto out;

		/* let, card state to settle a bit, and then do the work */
		dev->card_unstable = 1;
		queue_delayed_work(dev->card_workqueue,
			&dev->card_detect_work, msecs_to_jiffies(100));
		goto out;
	}


	/* Handle dma interrupts */
	dma_status = r852_read_reg_dword(dev, R852_DMA_IRQ_STA);
	r852_write_reg_dword(dev, R852_DMA_IRQ_STA, dma_status);

	if (dma_status & R852_DMA_IRQ_MASK) {

		ret = IRQ_HANDLED;

		if (dma_status & R852_DMA_IRQ_ERROR) {
			dbg("received dma error IRQ");
			r852_dma_done(dev, -EIO);
			complete(&dev->dma_done);
			goto out;
		}

		/* received DMA interrupt out of nowhere? */
		WARN_ON_ONCE(dev->dma_stage == 0);

		if (dev->dma_stage == 0)
			goto out;

		/* done device access */
		if (dev->dma_state == DMA_INTERNAL &&
				(dma_status & R852_DMA_IRQ_INTERNAL)) {

			dev->dma_state = DMA_MEMORY;
			dev->dma_stage++;
		}

		/* done memory DMA */
		if (dev->dma_state == DMA_MEMORY &&
				(dma_status & R852_DMA_IRQ_MEMORY)) {
			dev->dma_state = DMA_INTERNAL;
			dev->dma_stage++;
		}

		/* Enable 2nd half of dma dance */
		if (dev->dma_stage == 2)
			r852_dma_enable(dev);

		/* Operation done */
		if (dev->dma_stage == 3) {
			r852_dma_done(dev, 0);
			complete(&dev->dma_done);
		}
		goto out;
	}

	/* Handle unknown interrupts */
	if (dma_status)
		dbg("bad dma IRQ status = %x", dma_status);

	if (card_status & ~R852_CARD_STA_CD)
		dbg("strange card status = %x", card_status);

out:
	spin_unlock_irqrestore(&dev->irqlock, flags);
	return ret;
}