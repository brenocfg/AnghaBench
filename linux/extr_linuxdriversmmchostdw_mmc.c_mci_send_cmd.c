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
typedef  unsigned int u32 ;
struct dw_mci_slot {TYPE_1__* mmc; struct dw_mci* host; } ;
struct dw_mci {scalar_t__ regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CMDARG ; 
 scalar_t__ SDMMC_CMD ; 
 unsigned int SDMMC_CMD_START ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dw_mci_wait_while_busy (struct dw_mci*,unsigned int) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ readl_poll_timeout_atomic (scalar_t__,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mci_send_cmd(struct dw_mci_slot *slot, u32 cmd, u32 arg)
{
	struct dw_mci *host = slot->host;
	unsigned int cmd_status = 0;

	mci_writel(host, CMDARG, arg);
	wmb(); /* drain writebuffer */
	dw_mci_wait_while_busy(host, cmd);
	mci_writel(host, CMD, SDMMC_CMD_START | cmd);

	if (readl_poll_timeout_atomic(host->regs + SDMMC_CMD, cmd_status,
				      !(cmd_status & SDMMC_CMD_START),
				      1, 500 * USEC_PER_MSEC))
		dev_err(&slot->mmc->class_dev,
			"Timeout sending command (cmd %#x arg %#x status %#x)\n",
			cmd, arg, cmd_status);
}