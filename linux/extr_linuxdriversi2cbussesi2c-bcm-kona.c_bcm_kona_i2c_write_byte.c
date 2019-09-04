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
struct bcm_kona_i2c_dev {int /*<<< orphan*/  device; scalar_t__ base; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int CS_ACK_MASK ; 
 scalar_t__ CS_OFFSET ; 
 scalar_t__ DAT_OFFSET ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int /*<<< orphan*/  IER_I2C_INT_EN_MASK ; 
 scalar_t__ IER_OFFSET ; 
 scalar_t__ ISR_OFFSET ; 
 int /*<<< orphan*/  ISR_SES_DONE_MASK ; 
 int bcm_kona_i2c_wait_if_busy (struct bcm_kona_i2c_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm_kona_i2c_write_byte(struct bcm_kona_i2c_dev *dev, uint8_t data,
				   unsigned int nak_expected)
{
	int rc;
	unsigned long time_left = msecs_to_jiffies(I2C_TIMEOUT);
	unsigned int nak_received;

	/* Make sure the hardware is ready */
	rc = bcm_kona_i2c_wait_if_busy(dev);
	if (rc < 0)
		return rc;

	/* Clear pending session done interrupt */
	writel(ISR_SES_DONE_MASK, dev->base + ISR_OFFSET);

	/* Unmask the session done interrupt */
	writel(IER_I2C_INT_EN_MASK, dev->base + IER_OFFSET);

	/* Mark as incomplete before sending the data */
	reinit_completion(&dev->done);

	/* Send one byte of data */
	writel(data, dev->base + DAT_OFFSET);

	/* Wait for byte to be written */
	time_left = wait_for_completion_timeout(&dev->done, time_left);

	/* Mask all interrupts */
	writel(0, dev->base + IER_OFFSET);

	if (!time_left) {
		dev_dbg(dev->device, "controller timed out\n");
		return -ETIMEDOUT;
	}

	nak_received = readl(dev->base + CS_OFFSET) & CS_ACK_MASK ? 1 : 0;

	if (nak_received ^ nak_expected) {
		dev_dbg(dev->device, "unexpected NAK/ACK\n");
		return -EREMOTEIO;
	}

	return 0;
}