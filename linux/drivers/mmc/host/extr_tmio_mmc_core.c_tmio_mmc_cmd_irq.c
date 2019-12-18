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
struct tmio_mmc_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  done; int /*<<< orphan*/  dma_issue; int /*<<< orphan*/  dma_on; TYPE_1__* data; struct mmc_command* cmd; } ;
struct mmc_command {int* resp; int flags; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CTL_RESPONSE ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_CRC ; 
 int MMC_RSP_R3 ; 
 int /*<<< orphan*/  TMIO_MASK_READOP ; 
 int /*<<< orphan*/  TMIO_MASK_WRITEOP ; 
 unsigned int TMIO_STAT_CMDTIMEOUT ; 
 unsigned int TMIO_STAT_CMD_IDX_ERR ; 
 unsigned int TMIO_STAT_CRCFAIL ; 
 unsigned int TMIO_STAT_STOPBIT_ERR ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int sd_ctrl_read16_and_16_as_32 (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmio_mmc_disable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmio_mmc_enable_mmc_irqs (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmio_mmc_cmd_irq(struct tmio_mmc_host *host, unsigned int stat)
{
	struct mmc_command *cmd = host->cmd;
	int i, addr;

	spin_lock(&host->lock);

	if (!host->cmd) {
		pr_debug("Spurious CMD irq\n");
		goto out;
	}

	/* This controller is sicker than the PXA one. Not only do we need to
	 * drop the top 8 bits of the first response word, we also need to
	 * modify the order of the response for short response command types.
	 */

	for (i = 3, addr = CTL_RESPONSE ; i >= 0 ; i--, addr += 4)
		cmd->resp[i] = sd_ctrl_read16_and_16_as_32(host, addr);

	if (cmd->flags &  MMC_RSP_136) {
		cmd->resp[0] = (cmd->resp[0] << 8) | (cmd->resp[1] >> 24);
		cmd->resp[1] = (cmd->resp[1] << 8) | (cmd->resp[2] >> 24);
		cmd->resp[2] = (cmd->resp[2] << 8) | (cmd->resp[3] >> 24);
		cmd->resp[3] <<= 8;
	} else if (cmd->flags & MMC_RSP_R3) {
		cmd->resp[0] = cmd->resp[3];
	}

	if (stat & TMIO_STAT_CMDTIMEOUT)
		cmd->error = -ETIMEDOUT;
	else if ((stat & TMIO_STAT_CRCFAIL && cmd->flags & MMC_RSP_CRC) ||
		 stat & TMIO_STAT_STOPBIT_ERR ||
		 stat & TMIO_STAT_CMD_IDX_ERR)
		cmd->error = -EILSEQ;

	/* If there is data to handle we enable data IRQs here, and
	 * we will ultimatley finish the request in the data_end handler.
	 * If theres no data or we encountered an error, finish now.
	 */
	if (host->data && (!cmd->error || cmd->error == -EILSEQ)) {
		if (host->data->flags & MMC_DATA_READ) {
			if (!host->dma_on) {
				tmio_mmc_enable_mmc_irqs(host, TMIO_MASK_READOP);
			} else {
				tmio_mmc_disable_mmc_irqs(host,
							  TMIO_MASK_READOP);
				tasklet_schedule(&host->dma_issue);
			}
		} else {
			if (!host->dma_on) {
				tmio_mmc_enable_mmc_irqs(host, TMIO_MASK_WRITEOP);
			} else {
				tmio_mmc_disable_mmc_irqs(host,
							  TMIO_MASK_WRITEOP);
				tasklet_schedule(&host->dma_issue);
			}
		}
	} else {
		schedule_work(&host->done);
	}

out:
	spin_unlock(&host->lock);
}