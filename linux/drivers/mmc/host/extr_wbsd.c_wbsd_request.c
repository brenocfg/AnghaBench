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
struct wbsd_host {int flags; int dma; int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo_tasklet; int /*<<< orphan*/  mmc; struct mmc_request* mrq; } ;
struct mmc_request {struct mmc_command* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {int opcode; int /*<<< orphan*/  error; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int WBSD_FCARD_PRESENT ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 struct wbsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbsd_prepare_data (struct wbsd_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  wbsd_request_end (struct wbsd_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  wbsd_send_command (struct wbsd_host*,struct mmc_command*) ; 

__attribute__((used)) static void wbsd_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct wbsd_host *host = mmc_priv(mmc);
	struct mmc_command *cmd;

	/*
	 * Disable tasklets to avoid a deadlock.
	 */
	spin_lock_bh(&host->lock);

	BUG_ON(host->mrq != NULL);

	cmd = mrq->cmd;

	host->mrq = mrq;

	/*
	 * Check that there is actually a card in the slot.
	 */
	if (!(host->flags & WBSD_FCARD_PRESENT)) {
		cmd->error = -ENOMEDIUM;
		goto done;
	}

	if (cmd->data) {
		/*
		 * The hardware is so delightfully stupid that it has a list
		 * of "data" commands. If a command isn't on this list, it'll
		 * just go back to the idle state and won't send any data
		 * interrupts.
		 */
		switch (cmd->opcode) {
		case 11:
		case 17:
		case 18:
		case 20:
		case 24:
		case 25:
		case 26:
		case 27:
		case 30:
		case 42:
		case 56:
			break;

		/* ACMDs. We don't keep track of state, so we just treat them
		 * like any other command. */
		case 51:
			break;

		default:
			pr_warn("%s: Data command %d is not supported by this controller\n",
				mmc_hostname(host->mmc), cmd->opcode);
			cmd->error = -EINVAL;

			goto done;
		}
	}

	/*
	 * Does the request include data?
	 */
	if (cmd->data) {
		wbsd_prepare_data(host, cmd->data);

		if (cmd->data->error)
			goto done;
	}

	wbsd_send_command(host, cmd);

	/*
	 * If this is a data transfer the request
	 * will be finished after the data has
	 * transferred.
	 */
	if (cmd->data && !cmd->error) {
		/*
		 * Dirty fix for hardware bug.
		 */
		if (host->dma == -1)
			tasklet_schedule(&host->fifo_tasklet);

		spin_unlock_bh(&host->lock);

		return;
	}

done:
	wbsd_request_end(host, mrq);

	spin_unlock_bh(&host->lock);
}