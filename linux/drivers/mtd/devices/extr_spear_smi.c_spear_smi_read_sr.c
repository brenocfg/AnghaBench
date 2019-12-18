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
struct spear_smi {int status; int /*<<< orphan*/  lock; scalar_t__ io_base; int /*<<< orphan*/  cmd_complete; } ;

/* Variables and functions */
 int BANK_SHIFT ; 
 int ETIMEDOUT ; 
 int RD_STATUS_REG ; 
 int /*<<< orphan*/  SMI_CMD_TIMEOUT ; 
 scalar_t__ SMI_CR1 ; 
 scalar_t__ SMI_CR2 ; 
 int SW_MODE ; 
 int TFF ; 
 int TFIE ; 
 int WB_MODE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spear_smi_read_sr(struct spear_smi *dev, u32 bank)
{
	int ret;
	u32 ctrlreg1;

	mutex_lock(&dev->lock);
	dev->status = 0; /* Will be set in interrupt handler */

	ctrlreg1 = readl(dev->io_base + SMI_CR1);
	/* program smi in hw mode */
	writel(ctrlreg1 & ~(SW_MODE | WB_MODE), dev->io_base + SMI_CR1);

	/* performing a rsr instruction in hw mode */
	writel((bank << BANK_SHIFT) | RD_STATUS_REG | TFIE,
			dev->io_base + SMI_CR2);

	/* wait for tff */
	ret = wait_event_interruptible_timeout(dev->cmd_complete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	/* copy dev->status (lower 16 bits) in order to release lock */
	if (ret > 0)
		ret = dev->status & 0xffff;
	else if (ret == 0)
		ret = -ETIMEDOUT;

	/* restore the ctrl regs state */
	writel(ctrlreg1, dev->io_base + SMI_CR1);
	writel(0, dev->io_base + SMI_CR2);
	mutex_unlock(&dev->lock);

	return ret;
}