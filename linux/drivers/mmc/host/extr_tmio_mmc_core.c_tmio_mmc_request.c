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
struct tmio_mmc_host {int /*<<< orphan*/  lock; struct mmc_request* mrq; int /*<<< orphan*/  last_req_ts; } ;
struct mmc_request {TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ IS_ERR (struct mmc_request*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct tmio_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_process_mrq (struct tmio_mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void tmio_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct tmio_mmc_host *host = mmc_priv(mmc);
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	if (host->mrq) {
		pr_debug("request not null\n");
		if (IS_ERR(host->mrq)) {
			spin_unlock_irqrestore(&host->lock, flags);
			mrq->cmd->error = -EAGAIN;
			mmc_request_done(mmc, mrq);
			return;
		}
	}

	host->last_req_ts = jiffies;
	wmb();
	host->mrq = mrq;

	spin_unlock_irqrestore(&host->lock, flags);

	tmio_process_mrq(host, mrq);
}