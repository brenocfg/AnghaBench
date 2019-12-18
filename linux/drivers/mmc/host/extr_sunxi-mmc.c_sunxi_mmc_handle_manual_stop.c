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
struct sunxi_mmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  lock; struct mmc_request* manual_stop_mrq; } ;
struct mmc_request {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunxi_mmc_send_manual_stop (struct sunxi_mmc_host*,struct mmc_request*) ; 

__attribute__((used)) static irqreturn_t sunxi_mmc_handle_manual_stop(int irq, void *dev_id)
{
	struct sunxi_mmc_host *host = dev_id;
	struct mmc_request *mrq;
	unsigned long iflags;

	spin_lock_irqsave(&host->lock, iflags);
	mrq = host->manual_stop_mrq;
	spin_unlock_irqrestore(&host->lock, iflags);

	if (!mrq) {
		dev_err(mmc_dev(host->mmc), "no request for manual stop\n");
		return IRQ_HANDLED;
	}

	dev_err(mmc_dev(host->mmc), "data error, sending stop command\n");

	/*
	 * We will never have more than one outstanding request,
	 * and we do not complete the request until after
	 * we've cleared host->manual_stop_mrq so we do not need to
	 * spin lock this function.
	 * Additionally we have wait states within this function
	 * so having it in a lock is a very bad idea.
	 */
	sunxi_mmc_send_manual_stop(host, mrq);

	spin_lock_irqsave(&host->lock, iflags);
	host->manual_stop_mrq = NULL;
	spin_unlock_irqrestore(&host->lock, iflags);

	mmc_request_done(host->mmc, mrq);

	return IRQ_HANDLED;
}