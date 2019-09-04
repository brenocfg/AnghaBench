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
struct mmc_request {TYPE_1__* cmd; int /*<<< orphan*/  data; } ;
struct mmc_host {int dummy; } ;
struct au1xmmc_host {scalar_t__ status; struct mmc_request* mrq; } ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 int ENOMEDIUM ; 
 int /*<<< orphan*/  FLUSH_FIFO (struct au1xmmc_host*) ; 
 scalar_t__ HOST_S_CMD ; 
 scalar_t__ HOST_S_IDLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ au1xmmc_card_inserted (struct mmc_host*) ; 
 int /*<<< orphan*/  au1xmmc_finish_request (struct au1xmmc_host*) ; 
 int au1xmmc_prepare_data (struct au1xmmc_host*,int /*<<< orphan*/ ) ; 
 int au1xmmc_send_command (struct au1xmmc_host*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int irqs_disabled () ; 
 struct au1xmmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void au1xmmc_request(struct mmc_host* mmc, struct mmc_request* mrq)
{
	struct au1xmmc_host *host = mmc_priv(mmc);
	int ret = 0;

	WARN_ON(irqs_disabled());
	WARN_ON(host->status != HOST_S_IDLE);

	host->mrq = mrq;
	host->status = HOST_S_CMD;

	/* fail request immediately if no card is present */
	if (0 == au1xmmc_card_inserted(mmc)) {
		mrq->cmd->error = -ENOMEDIUM;
		au1xmmc_finish_request(host);
		return;
	}

	if (mrq->data) {
		FLUSH_FIFO(host);
		ret = au1xmmc_prepare_data(host, mrq->data);
	}

	if (!ret)
		ret = au1xmmc_send_command(host, 0, mrq->cmd, mrq->data);

	if (ret) {
		mrq->cmd->error = ret;
		au1xmmc_finish_request(host);
	}
}