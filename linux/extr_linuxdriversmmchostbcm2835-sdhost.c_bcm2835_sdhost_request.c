#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmc_request {TYPE_3__* data; struct mmc_command* cmd; struct mmc_command* sbc; TYPE_2__* stop; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {struct mmc_request* opcode; scalar_t__ error; int /*<<< orphan*/  flags; int /*<<< orphan*/  arg; TYPE_1__* data; } ;
struct bcm2835_host {scalar_t__ pio_limit; int use_sbc; int /*<<< orphan*/  lock; int /*<<< orphan*/  use_busy; scalar_t__ dma_desc; scalar_t__ data; struct mmc_request* mrq; int /*<<< orphan*/  finish_tasklet; struct mmc_host* mmc; scalar_t__ debug; int /*<<< orphan*/  clock; scalar_t__ reset_clock; scalar_t__ use_dma; } ;
struct TYPE_6__ {scalar_t__ blocks; int flags; scalar_t__ blksz; scalar_t__ error; } ;
struct TYPE_5__ {scalar_t__ error; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  blksz; int /*<<< orphan*/  blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EILSEQ ; 
 scalar_t__ EINVAL ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDCMD ; 
 int SDCMD_CMD_MASK ; 
 int /*<<< orphan*/  SDEDM ; 
 int SDEDM_FSM_DATAMODE ; 
 int SDEDM_FSM_IDENTMODE ; 
 int SDEDM_FSM_MASK ; 
 int USE_CMD23_FLAGS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_finish_command (struct bcm2835_host*,unsigned long*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_prepare_dma (struct bcm2835_host*,TYPE_3__*) ; 
 int bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ bcm2835_sdhost_send_command (struct bcm2835_host*,struct mmc_command*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_set_clock (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_start_dma (struct bcm2835_host*) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int /*<<< orphan*/  log_dump () ; 
 int /*<<< orphan*/  log_event (char*,struct mmc_request*,int) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,struct mmc_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_sdhost_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct bcm2835_host *host;
	unsigned long flags;
	u32 edm, fsm;

	host = mmc_priv(mmc);

	if (host->debug) {
		struct mmc_command *cmd = mrq->cmd;
		BUG_ON(!cmd);
		if (cmd->data)
			pr_info("%s: cmd %d 0x%x (flags 0x%x) - %s %d*%d\n",
				mmc_hostname(mmc),
				cmd->opcode, cmd->arg, cmd->flags,
				(cmd->data->flags & MMC_DATA_READ) ?
				"read" : "write", cmd->data->blocks,
				cmd->data->blksz);
		else
			pr_info("%s: cmd %d 0x%x (flags 0x%x)\n",
				mmc_hostname(mmc),
				cmd->opcode, cmd->arg, cmd->flags);
	}

	/* Reset the error statuses in case this is a retry */
	if (mrq->sbc)
		mrq->sbc->error = 0;
	if (mrq->cmd)
		mrq->cmd->error = 0;
	if (mrq->data)
		mrq->data->error = 0;
	if (mrq->stop)
		mrq->stop->error = 0;

	if (mrq->data && !is_power_of_2(mrq->data->blksz)) {
		pr_err("%s: unsupported block size (%d bytes)\n",
		       mmc_hostname(mmc), mrq->data->blksz);
		mrq->cmd->error = -EINVAL;
		mmc_request_done(mmc, mrq);
		return;
	}

	if (host->use_dma && mrq->data &&
	    (mrq->data->blocks > host->pio_limit))
		bcm2835_sdhost_prepare_dma(host, mrq->data);

	if (host->reset_clock)
	    bcm2835_sdhost_set_clock(host, host->clock);

	spin_lock_irqsave(&host->lock, flags);

	WARN_ON(host->mrq != NULL);
	host->mrq = mrq;

	edm = bcm2835_sdhost_read(host, SDEDM);
	fsm = edm & SDEDM_FSM_MASK;

	log_event("REQ<", mrq, edm);
	if ((fsm != SDEDM_FSM_IDENTMODE) &&
	    (fsm != SDEDM_FSM_DATAMODE)) {
		log_event("REQ!", mrq, edm);
		if (host->debug) {
			pr_warn("%s: previous command (%d) not complete (EDM %x)\n",
			       mmc_hostname(host->mmc),
			       bcm2835_sdhost_read(host, SDCMD) & SDCMD_CMD_MASK,
			       edm);
			log_dump();
			bcm2835_sdhost_dumpregs(host);
		}
		mrq->cmd->error = -EILSEQ;
		tasklet_schedule(&host->finish_tasklet);
		mmiowb();
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	host->use_sbc = !!mrq->sbc &&
		(host->mrq->data->flags & USE_CMD23_FLAGS);
	if (host->use_sbc) {
		if (bcm2835_sdhost_send_command(host, mrq->sbc)) {
			if (!host->use_busy)
				bcm2835_sdhost_finish_command(host, &flags);
		}
	} else if (bcm2835_sdhost_send_command(host, mrq->cmd)) {
		if (host->data && host->dma_desc)
			/* DMA transfer starts now, PIO starts after irq */
			bcm2835_sdhost_start_dma(host);

		if (!host->use_busy)
			bcm2835_sdhost_finish_command(host, &flags);
	}

	log_event("CMD ", mrq->cmd->opcode,
		   mrq->data ? (u32)mrq->data->blksz : 0);
	mmiowb();

	log_event("REQ>", mrq, 0);
	spin_unlock_irqrestore(&host->lock, flags);
}