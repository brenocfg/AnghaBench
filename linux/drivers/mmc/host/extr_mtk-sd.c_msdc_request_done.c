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
struct msdc_host {int /*<<< orphan*/  mmc; scalar_t__ error; int /*<<< orphan*/  lock; int /*<<< orphan*/ * mrq; int /*<<< orphan*/  req_timeout; } ;
struct mmc_request {scalar_t__ data; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  msdc_reset_hw (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_track_cmd_data (struct msdc_host*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msdc_unprepare_data (struct msdc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void msdc_request_done(struct msdc_host *host, struct mmc_request *mrq)
{
	unsigned long flags;
	bool ret;

	ret = cancel_delayed_work(&host->req_timeout);
	if (!ret) {
		/* delay work already running */
		return;
	}
	spin_lock_irqsave(&host->lock, flags);
	host->mrq = NULL;
	spin_unlock_irqrestore(&host->lock, flags);

	msdc_track_cmd_data(host, mrq->cmd, mrq->data);
	if (mrq->data)
		msdc_unprepare_data(host, mrq);
	if (host->error)
		msdc_reset_hw(host);
	mmc_request_done(host->mmc, mrq);
}