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
struct bcm_kona_i2c_dev {int /*<<< orphan*/  device; scalar_t__ base; int /*<<< orphan*/  done; } ;
typedef  enum bcm_kona_cmd_t { ____Placeholder_bcm_kona_cmd_t } bcm_kona_cmd_t ;

/* Variables and functions */
 int BCM_CMD_NOACTION ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int /*<<< orphan*/  IER_I2C_INT_EN_MASK ; 
 scalar_t__ IER_OFFSET ; 
 int /*<<< orphan*/  bcm_kona_i2c_send_cmd_to_ctrl (struct bcm_kona_i2c_dev*,int) ; 
 int bcm_kona_i2c_wait_if_busy (struct bcm_kona_i2c_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm_kona_send_i2c_cmd(struct bcm_kona_i2c_dev *dev,
				 enum bcm_kona_cmd_t cmd)
{
	int rc;
	unsigned long time_left = msecs_to_jiffies(I2C_TIMEOUT);

	/* Make sure the hardware is ready */
	rc = bcm_kona_i2c_wait_if_busy(dev);
	if (rc < 0)
		return rc;

	/* Unmask the session done interrupt */
	writel(IER_I2C_INT_EN_MASK, dev->base + IER_OFFSET);

	/* Mark as incomplete before sending the command */
	reinit_completion(&dev->done);

	/* Send the command */
	bcm_kona_i2c_send_cmd_to_ctrl(dev, cmd);

	/* Wait for transaction to finish or timeout */
	time_left = wait_for_completion_timeout(&dev->done, time_left);

	/* Mask all interrupts */
	writel(0, dev->base + IER_OFFSET);

	if (!time_left) {
		dev_err(dev->device, "controller timed out\n");
		rc = -ETIMEDOUT;
	}

	/* Clear command */
	bcm_kona_i2c_send_cmd_to_ctrl(dev, BCM_CMD_NOACTION);

	return rc;
}