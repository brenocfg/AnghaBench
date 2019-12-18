#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmc_command {int busy_timeout; int flags; int arg; int opcode; TYPE_2__* data; int /*<<< orphan*/  error; } ;
struct device {int dummy; } ;
struct bcm2835_host {int use_busy; scalar_t__ ioaddr; struct mmc_command* cmd; int /*<<< orphan*/  timeout_work; TYPE_1__* pdev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int HZ ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_WRITE ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_BUSY ; 
 int MMC_RSP_PRESENT ; 
 scalar_t__ SDARG ; 
 scalar_t__ SDCMD ; 
 int SDCMD_BUSYWAIT ; 
 int SDCMD_CMD_MASK ; 
 int SDCMD_LONG_RESPONSE ; 
 int SDCMD_NEW_FLAG ; 
 int SDCMD_NO_RESPONSE ; 
 int SDCMD_READ_CMD ; 
 int SDCMD_WRITE_CMD ; 
 scalar_t__ SDHSTS ; 
 int SDHSTS_ERROR_MASK ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_command*) ; 
 int /*<<< orphan*/  bcm2835_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_finish_request (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_prepare_data (struct bcm2835_host*,struct mmc_command*) ; 
 int bcm2835_read_wait_sdcmd (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static
bool bcm2835_send_command(struct bcm2835_host *host, struct mmc_command *cmd)
{
	struct device *dev = &host->pdev->dev;
	u32 sdcmd, sdhsts;
	unsigned long timeout;

	WARN_ON(host->cmd);

	sdcmd = bcm2835_read_wait_sdcmd(host, 100);
	if (sdcmd & SDCMD_NEW_FLAG) {
		dev_err(dev, "previous command never completed.\n");
		bcm2835_dumpregs(host);
		cmd->error = -EILSEQ;
		bcm2835_finish_request(host);
		return false;
	}

	if (!cmd->data && cmd->busy_timeout > 9000)
		timeout = DIV_ROUND_UP(cmd->busy_timeout, 1000) * HZ + HZ;
	else
		timeout = 10 * HZ;
	schedule_delayed_work(&host->timeout_work, timeout);

	host->cmd = cmd;

	/* Clear any error flags */
	sdhsts = readl(host->ioaddr + SDHSTS);
	if (sdhsts & SDHSTS_ERROR_MASK)
		writel(sdhsts, host->ioaddr + SDHSTS);

	if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) {
		dev_err(dev, "unsupported response type!\n");
		cmd->error = -EINVAL;
		bcm2835_finish_request(host);
		return false;
	}

	bcm2835_prepare_data(host, cmd);

	writel(cmd->arg, host->ioaddr + SDARG);

	sdcmd = cmd->opcode & SDCMD_CMD_MASK;

	host->use_busy = false;
	if (!(cmd->flags & MMC_RSP_PRESENT)) {
		sdcmd |= SDCMD_NO_RESPONSE;
	} else {
		if (cmd->flags & MMC_RSP_136)
			sdcmd |= SDCMD_LONG_RESPONSE;
		if (cmd->flags & MMC_RSP_BUSY) {
			sdcmd |= SDCMD_BUSYWAIT;
			host->use_busy = true;
		}
	}

	if (cmd->data) {
		if (cmd->data->flags & MMC_DATA_WRITE)
			sdcmd |= SDCMD_WRITE_CMD;
		if (cmd->data->flags & MMC_DATA_READ)
			sdcmd |= SDCMD_READ_CMD;
	}

	writel(sdcmd | SDCMD_NEW_FLAG, host->ioaddr + SDCMD);

	return true;
}