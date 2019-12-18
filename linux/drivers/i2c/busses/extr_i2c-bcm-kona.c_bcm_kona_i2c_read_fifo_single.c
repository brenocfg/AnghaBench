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
typedef  int /*<<< orphan*/  uint8_t ;
struct bcm_kona_i2c_dev {scalar_t__ base; int /*<<< orphan*/  device; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 scalar_t__ IER_OFFSET ; 
 unsigned int IER_READ_COMPLETE_INT_MASK ; 
 unsigned int RXFCR_NACK_EN_SHIFT ; 
 scalar_t__ RXFCR_OFFSET ; 
 unsigned int RXFCR_READ_COUNT_SHIFT ; 
 scalar_t__ RXFIFORDOUT_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int bcm_kona_i2c_read_fifo_single(struct bcm_kona_i2c_dev *dev,
					 uint8_t *buf, unsigned int len,
					 unsigned int last_byte_nak)
{
	unsigned long time_left = msecs_to_jiffies(I2C_TIMEOUT);

	/* Mark as incomplete before starting the RX FIFO */
	reinit_completion(&dev->done);

	/* Unmask the read complete interrupt */
	writel(IER_READ_COMPLETE_INT_MASK, dev->base + IER_OFFSET);

	/* Start the RX FIFO */
	writel((last_byte_nak << RXFCR_NACK_EN_SHIFT) |
	       (len << RXFCR_READ_COUNT_SHIFT),
		dev->base + RXFCR_OFFSET);

	/* Wait for FIFO read to complete */
	time_left = wait_for_completion_timeout(&dev->done, time_left);

	/* Mask all interrupts */
	writel(0, dev->base + IER_OFFSET);

	if (!time_left) {
		dev_err(dev->device, "RX FIFO time out\n");
		return -EREMOTEIO;
	}

	/* Read data from FIFO */
	for (; len > 0; len--, buf++)
		*buf = readl(dev->base + RXFIFORDOUT_OFFSET);

	return 0;
}