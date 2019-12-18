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
struct bcm_kona_i2c_dev {int /*<<< orphan*/  device; scalar_t__ base; int /*<<< orphan*/  done; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CS_ACK_MASK ; 
 scalar_t__ CS_OFFSET ; 
 scalar_t__ DAT_OFFSET ; 
 int EREMOTEIO ; 
 scalar_t__ FIFO_STATUS_OFFSET ; 
 unsigned int FIFO_STATUS_TXFIFO_EMPTY_MASK ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int IER_FIFO_INT_EN_MASK ; 
 int IER_NOACK_EN_MASK ; 
 scalar_t__ IER_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bcm_kona_i2c_write_fifo_single(struct bcm_kona_i2c_dev *dev,
					  uint8_t *buf, unsigned int len)
{
	int k;
	unsigned long time_left = msecs_to_jiffies(I2C_TIMEOUT);
	unsigned int fifo_status;

	/* Mark as incomplete before sending data to the TX FIFO */
	reinit_completion(&dev->done);

	/* Unmask the fifo empty and nak interrupt */
	writel(IER_FIFO_INT_EN_MASK | IER_NOACK_EN_MASK,
	       dev->base + IER_OFFSET);

	/* Disable IRQ to load a FIFO worth of data without interruption */
	disable_irq(dev->irq);

	/* Write data into FIFO */
	for (k = 0; k < len; k++)
		writel(buf[k], (dev->base + DAT_OFFSET));

	/* Enable IRQ now that data has been loaded */
	enable_irq(dev->irq);

	/* Wait for FIFO to empty */
	do {
		time_left = wait_for_completion_timeout(&dev->done, time_left);
		fifo_status = readl(dev->base + FIFO_STATUS_OFFSET);
	} while (time_left && !(fifo_status & FIFO_STATUS_TXFIFO_EMPTY_MASK));

	/* Mask all interrupts */
	writel(0, dev->base + IER_OFFSET);

	/* Check if there was a NAK */
	if (readl(dev->base + CS_OFFSET) & CS_ACK_MASK) {
		dev_err(dev->device, "unexpected NAK\n");
		return -EREMOTEIO;
	}

	/* Check if a timeout occured */
	if (!time_left) {
		dev_err(dev->device, "completion timed out\n");
		return -EREMOTEIO;
	}

	return 0;
}