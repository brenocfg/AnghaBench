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
struct mmc_command {int arg; } ;
struct dw_mci {int /*<<< orphan*/  dev; struct mmc_command* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CMDARG ; 
 int SDMMC_CMD_RESP_EXP ; 
 int SDMMC_CMD_START ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dw_mci_set_cto (struct dw_mci*) ; 
 int /*<<< orphan*/  dw_mci_wait_while_busy (struct dw_mci*,int) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dw_mci_start_command(struct dw_mci *host,
				 struct mmc_command *cmd, u32 cmd_flags)
{
	host->cmd = cmd;
	dev_vdbg(host->dev,
		 "start command: ARGR=0x%08x CMDR=0x%08x\n",
		 cmd->arg, cmd_flags);

	mci_writel(host, CMDARG, cmd->arg);
	wmb(); /* drain writebuffer */
	dw_mci_wait_while_busy(host, cmd_flags);

	mci_writel(host, CMD, cmd_flags | SDMMC_CMD_START);

	/* response expected command only */
	if (cmd_flags & SDMMC_CMD_RESP_EXP)
		dw_mci_set_cto(host);
}