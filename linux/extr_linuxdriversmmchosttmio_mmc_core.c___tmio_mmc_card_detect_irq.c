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
struct tmio_mmc_host {struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct mmc_host {TYPE_1__ detect; scalar_t__ card; } ;

/* Variables and functions */
 int TMIO_STAT_CARD_INSERT ; 
 int TMIO_STAT_CARD_REMOVE ; 
 int /*<<< orphan*/  mmc_detect_change (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  tmio_mmc_ack_mmc_irqs (struct tmio_mmc_host*,int) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __tmio_mmc_card_detect_irq(struct tmio_mmc_host *host,
				       int ireg, int status)
{
	struct mmc_host *mmc = host->mmc;

	/* Card insert / remove attempts */
	if (ireg & (TMIO_STAT_CARD_INSERT | TMIO_STAT_CARD_REMOVE)) {
		tmio_mmc_ack_mmc_irqs(host, TMIO_STAT_CARD_INSERT |
			TMIO_STAT_CARD_REMOVE);
		if ((((ireg & TMIO_STAT_CARD_REMOVE) && mmc->card) ||
		     ((ireg & TMIO_STAT_CARD_INSERT) && !mmc->card)) &&
		    !work_pending(&mmc->detect.work))
			mmc_detect_change(host->mmc, msecs_to_jiffies(100));
		return true;
	}

	return false;
}