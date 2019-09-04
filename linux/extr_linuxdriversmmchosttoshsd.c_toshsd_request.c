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
struct toshsd_host {int /*<<< orphan*/  lock; struct mmc_request* mrq; scalar_t__ ioaddr; } ;
struct mmc_request {TYPE_1__* cmd; int /*<<< orphan*/  data; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 scalar_t__ SD_CARDSTATUS ; 
 int SD_CARD_PRESENT_0 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int ioread16 (scalar_t__) ; 
 struct toshsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  toshsd_set_led (struct toshsd_host*,int) ; 
 int /*<<< orphan*/  toshsd_start_cmd (struct toshsd_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  toshsd_start_data (struct toshsd_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toshsd_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct toshsd_host *host = mmc_priv(mmc);
	unsigned long flags;

	/* abort if card not present */
	if (!(ioread16(host->ioaddr + SD_CARDSTATUS) & SD_CARD_PRESENT_0)) {
		mrq->cmd->error = -ENOMEDIUM;
		mmc_request_done(mmc, mrq);
		return;
	}

	spin_lock_irqsave(&host->lock, flags);

	WARN_ON(host->mrq != NULL);

	host->mrq = mrq;

	if (mrq->data)
		toshsd_start_data(host, mrq->data);

	toshsd_set_led(host, 1);

	toshsd_start_cmd(host, mrq->cmd);

	spin_unlock_irqrestore(&host->lock, flags);
}