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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_request {int dummy; } ;
struct mmc_data {int blksz; int blocks; } ;
struct mmc_command {scalar_t__ opcode; struct mmc_data* data; } ;
struct dw_mci_slot {int /*<<< orphan*/  flags; int /*<<< orphan*/  mmc; struct mmc_request* mrq; } ;
struct dw_mci {int /*<<< orphan*/  stop_cmdr; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  cmd11_timer; scalar_t__ pending_events; scalar_t__ dir_status; scalar_t__ data_status; scalar_t__ cmd_status; scalar_t__ completed_events; struct mmc_request* mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKSIZ ; 
 int /*<<< orphan*/  BYTCNT ; 
 int /*<<< orphan*/  DW_MMC_CARD_NEED_INIT ; 
 int /*<<< orphan*/  EVENT_CMD_COMPLETE ; 
 int /*<<< orphan*/  SDMMC_CMD_INIT ; 
 scalar_t__ SD_SWITCH_VOLTAGE ; 
 int /*<<< orphan*/  TMOUT ; 
 int /*<<< orphan*/  dw_mci_prep_stop_abort (struct dw_mci*,struct mmc_command*) ; 
 int /*<<< orphan*/  dw_mci_prepare_command (int /*<<< orphan*/ ,struct mmc_command*) ; 
 int /*<<< orphan*/  dw_mci_start_command (struct dw_mci*,struct mmc_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mci_submit_data (struct dw_mci*,struct mmc_data*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __dw_mci_start_request(struct dw_mci *host,
				   struct dw_mci_slot *slot,
				   struct mmc_command *cmd)
{
	struct mmc_request *mrq;
	struct mmc_data	*data;
	u32 cmdflags;

	mrq = slot->mrq;

	host->mrq = mrq;

	host->pending_events = 0;
	host->completed_events = 0;
	host->cmd_status = 0;
	host->data_status = 0;
	host->dir_status = 0;

	data = cmd->data;
	if (data) {
		mci_writel(host, TMOUT, 0xFFFFFFFF);
		mci_writel(host, BYTCNT, data->blksz*data->blocks);
		mci_writel(host, BLKSIZ, data->blksz);
	}

	cmdflags = dw_mci_prepare_command(slot->mmc, cmd);

	/* this is the first command, send the initialization clock */
	if (test_and_clear_bit(DW_MMC_CARD_NEED_INIT, &slot->flags))
		cmdflags |= SDMMC_CMD_INIT;

	if (data) {
		dw_mci_submit_data(host, data);
		wmb(); /* drain writebuffer */
	}

	dw_mci_start_command(host, cmd, cmdflags);

	if (cmd->opcode == SD_SWITCH_VOLTAGE) {
		unsigned long irqflags;

		/*
		 * Databook says to fail after 2ms w/ no response, but evidence
		 * shows that sometimes the cmd11 interrupt takes over 130ms.
		 * We'll set to 500ms, plus an extra jiffy just in case jiffies
		 * is just about to roll over.
		 *
		 * We do this whole thing under spinlock and only if the
		 * command hasn't already completed (indicating the the irq
		 * already ran so we don't want the timeout).
		 */
		spin_lock_irqsave(&host->irq_lock, irqflags);
		if (!test_bit(EVENT_CMD_COMPLETE, &host->pending_events))
			mod_timer(&host->cmd11_timer,
				jiffies + msecs_to_jiffies(500) + 1);
		spin_unlock_irqrestore(&host->irq_lock, irqflags);
	}

	host->stop_cmdr = dw_mci_prep_stop_abort(host, cmd);
}