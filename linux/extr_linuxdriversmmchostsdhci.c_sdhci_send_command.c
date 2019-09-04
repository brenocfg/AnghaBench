#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdhci_host {int quirks2; scalar_t__ data_timeout; int /*<<< orphan*/  mmc; struct mmc_command* data_cmd; struct mmc_command* cmd; } ;
struct mmc_command {scalar_t__ opcode; int flags; int busy_timeout; TYPE_2__* mrq; scalar_t__ data; int /*<<< orphan*/  error; int /*<<< orphan*/  arg; } ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {struct mmc_command* stop; } ;

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
 scalar_t__ MMC_SEND_TUNING_BLOCK ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK_HS200 ; 
 scalar_t__ MMC_STOP_TRANSMISSION ; 
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
 int /*<<< orphan*/  SDHCI_MAKE_CMD (scalar_t__,int) ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_QUIRK2_STOP_WITH_TC ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_command*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 scalar_t__ nsecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_data_line_cmd (struct mmc_command*) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_finish_mrq (struct sdhci_host*,TYPE_2__*) ; 
 int /*<<< orphan*/  sdhci_mod_timer (struct sdhci_host*,TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  sdhci_prepare_data (struct sdhci_host*,struct mmc_command*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_set_transfer_mode (struct sdhci_host*,struct mmc_command*) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sdhci_send_command(struct sdhci_host *host, struct mmc_command *cmd)
{
	int flags;
	u32 mask;
	unsigned long timeout;

	WARN_ON(host->cmd);

	/* Initially, a command has no error */
	cmd->error = 0;

	if ((host->quirks2 & SDHCI_QUIRK2_STOP_WITH_TC) &&
	    cmd->opcode == MMC_STOP_TRANSMISSION)
		cmd->flags |= MMC_RSP_BUSY;

	/* Wait max 10 ms */
	timeout = 10;

	mask = SDHCI_CMD_INHIBIT;
	if (sdhci_data_line_cmd(cmd))
		mask |= SDHCI_DATA_INHIBIT;

	/* We shouldn't wait for data inihibit for stop commands, even
	   though they might use busy signaling */
	if (cmd->mrq->data && (cmd == cmd->mrq->data->stop))
		mask &= ~SDHCI_DATA_INHIBIT;

	while (sdhci_readl(host, SDHCI_PRESENT_STATE) & mask) {
		if (timeout == 0) {
			pr_err("%s: Controller never released inhibit bit(s).\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			cmd->error = -EIO;
			sdhci_finish_mrq(host, cmd->mrq);
			return;
		}
		timeout--;
		mdelay(1);
	}

	host->cmd = cmd;
	if (sdhci_data_line_cmd(cmd)) {
		WARN_ON(host->data_cmd);
		host->data_cmd = cmd;
	}

	sdhci_prepare_data(host, cmd);

	sdhci_writel(host, cmd->arg, SDHCI_ARGUMENT);

	sdhci_set_transfer_mode(host, cmd);

	if ((cmd->flags & MMC_RSP_136) && (cmd->flags & MMC_RSP_BUSY)) {
		pr_err("%s: Unsupported response type!\n",
			mmc_hostname(host->mmc));
		cmd->error = -EINVAL;
		sdhci_finish_mrq(host, cmd->mrq);
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

	/* CMD19 is special in that the Data Present Select should be set */
	if (cmd->data || cmd->opcode == MMC_SEND_TUNING_BLOCK ||
	    cmd->opcode == MMC_SEND_TUNING_BLOCK_HS200)
		flags |= SDHCI_CMD_DATA;

	timeout = jiffies;
	if (host->data_timeout)
		timeout += nsecs_to_jiffies(host->data_timeout);
	else if (!cmd->data && cmd->busy_timeout > 9000)
		timeout += DIV_ROUND_UP(cmd->busy_timeout, 1000) * HZ + HZ;
	else
		timeout += 10 * HZ;
	sdhci_mod_timer(host, cmd->mrq, timeout);

	sdhci_writew(host, SDHCI_MAKE_CMD(cmd->opcode, flags), SDHCI_COMMAND);
}