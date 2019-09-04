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
struct mmc_command {int flags; int busy_timeout; int /*<<< orphan*/  opcode; int /*<<< orphan*/ * data; int /*<<< orphan*/  error; int /*<<< orphan*/  arg; } ;
struct bcm2835_host {int max_delay; int use_dma; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  mmc; struct mmc_command* cmd; int /*<<< orphan*/  timer; TYPE_2__* mrq; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {struct mmc_command* stop; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 unsigned long HZ ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_BUSY ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_OPCODE ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  SDHCI_ARGUMENT ; 
 int SDHCI_CMD_CRC ; 
 int SDHCI_CMD_DATA ; 
 int SDHCI_CMD_INDEX ; 
 int SDHCI_CMD_INHIBIT ; 
 int SDHCI_CMD_RESP_LONG ; 
 int SDHCI_CMD_RESP_NONE ; 
 int SDHCI_CMD_RESP_SHORT ; 
 int SDHCI_CMD_RESP_SHORT_BUSY ; 
 int /*<<< orphan*/  SDHCI_COMMAND ; 
 int SDHCI_DATA_INHIBIT ; 
 int /*<<< orphan*/  SDHCI_MAKE_CMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_command*) ; 
 int /*<<< orphan*/  bcm2835_mmc_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_mmc_prepare_data (struct bcm2835_host*,struct mmc_command*) ; 
 int bcm2835_mmc_readl (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_set_transfer_mode (struct bcm2835_host*,struct mmc_command*) ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835_mmc_writew (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

void bcm2835_mmc_send_command(struct bcm2835_host *host, struct mmc_command *cmd)
{
	int flags;
	u32 mask;
	unsigned long timeout;

	WARN_ON(host->cmd);

	/* Wait max 10 ms */
	timeout = 1000;

	mask = SDHCI_CMD_INHIBIT;
	if ((cmd->data != NULL) || (cmd->flags & MMC_RSP_BUSY))
		mask |= SDHCI_DATA_INHIBIT;

	/* We shouldn't wait for data inihibit for stop commands, even
	   though they might use busy signaling */
	if (host->mrq->data && (cmd == host->mrq->data->stop))
		mask &= ~SDHCI_DATA_INHIBIT;

	while (bcm2835_mmc_readl(host, SDHCI_PRESENT_STATE) & mask) {
		if (timeout == 0) {
			pr_err("%s: Controller never released inhibit bit(s).\n",
				mmc_hostname(host->mmc));
			bcm2835_mmc_dumpregs(host);
			cmd->error = -EIO;
			tasklet_schedule(&host->finish_tasklet);
			return;
		}
		timeout--;
		udelay(10);
	}

	if ((1000-timeout)/100 > 1 && (1000-timeout)/100 > host->max_delay) {
		host->max_delay = (1000-timeout)/100;
		pr_warning("Warning: MMC controller hung for %d ms\n", host->max_delay);
	}

	timeout = jiffies;
	if (!cmd->data && cmd->busy_timeout > 9000)
		timeout += DIV_ROUND_UP(cmd->busy_timeout, 1000) * HZ + HZ;
	else
		timeout += 10 * HZ;
	mod_timer(&host->timer, timeout);

	host->cmd = cmd;
	host->use_dma = false;

	bcm2835_mmc_prepare_data(host, cmd);

	bcm2835_mmc_writel(host, cmd->arg, SDHCI_ARGUMENT, 6);

	bcm2835_mmc_set_transfer_mode(host, cmd);

	if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) {
		pr_err("%s: Unsupported response type!\n",
			mmc_hostname(host->mmc));
		cmd->error = -EINVAL;
		tasklet_schedule(&host->finish_tasklet);
		return;
	}

	if (!(cmd->flags & MMC_RSP_PRESENT))
		flags = SDHCI_CMD_RESP_NONE;
	else if (cmd->flags & MMC_RSP_136)
		flags = SDHCI_CMD_RESP_LONG;
	else if (cmd->flags & MMC_RSP_BUSY)
		flags = SDHCI_CMD_RESP_SHORT_BUSY;
	else
		flags = SDHCI_CMD_RESP_SHORT;

	if (cmd->flags & MMC_RSP_CRC)
		flags |= SDHCI_CMD_CRC;
	if (cmd->flags & MMC_RSP_OPCODE)
		flags |= SDHCI_CMD_INDEX;

	if (cmd->data)
		flags |= SDHCI_CMD_DATA;

	bcm2835_mmc_writew(host, SDHCI_MAKE_CMD(cmd->opcode, flags), SDHCI_COMMAND);
}