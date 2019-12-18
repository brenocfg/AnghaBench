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
typedef  int u32 ;
struct spear_smi {int status; int /*<<< orphan*/  lock; scalar_t__ io_base; TYPE_1__* pdev; int /*<<< orphan*/  cmd_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BANK_SHIFT ; 
 int EIO ; 
 int SEND ; 
 int /*<<< orphan*/  SMI_CMD_TIMEOUT ; 
 scalar_t__ SMI_CR1 ; 
 scalar_t__ SMI_CR2 ; 
 int /*<<< orphan*/  SMI_MAX_TIME_OUT ; 
 scalar_t__ SMI_TR ; 
 int SW_MODE ; 
 int TFF ; 
 int TFIE ; 
 int TX_LEN_SHIFT ; 
 int WB_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int spear_smi_wait_till_ready (struct spear_smi*,int,int /*<<< orphan*/ ) ; 
 int spear_smi_write_enable (struct spear_smi*,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spear_smi_erase_sector(struct spear_smi *dev,
		u32 bank, u32 command, u32 bytes)
{
	u32 ctrlreg1 = 0;
	int ret;

	ret = spear_smi_wait_till_ready(dev, bank, SMI_MAX_TIME_OUT);
	if (ret)
		return ret;

	ret = spear_smi_write_enable(dev, bank);
	if (ret)
		return ret;

	mutex_lock(&dev->lock);

	ctrlreg1 = readl(dev->io_base + SMI_CR1);
	writel((ctrlreg1 | SW_MODE) & ~WB_MODE, dev->io_base + SMI_CR1);

	/* send command in sw mode */
	writel(command, dev->io_base + SMI_TR);

	writel((bank << BANK_SHIFT) | SEND | TFIE | (bytes << TX_LEN_SHIFT),
			dev->io_base + SMI_CR2);

	ret = wait_event_interruptible_timeout(dev->cmd_complete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	if (ret == 0) {
		ret = -EIO;
		dev_err(&dev->pdev->dev, "sector erase failed\n");
	} else if (ret > 0)
		ret = 0; /* success */

	/* restore ctrl regs */
	writel(ctrlreg1, dev->io_base + SMI_CR1);
	writel(0, dev->io_base + SMI_CR2);

	mutex_unlock(&dev->lock);
	return ret;
}