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
struct mmc_queue {int /*<<< orphan*/  use_cqe; struct mmc_card* card; } ;
struct mmc_host {int /*<<< orphan*/  cqe_enabled; } ;
struct mmc_card {struct mmc_host* host; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int mmc_mq_init (struct mmc_queue*,struct mmc_card*,int /*<<< orphan*/ *) ; 

int mmc_init_queue(struct mmc_queue *mq, struct mmc_card *card,
		   spinlock_t *lock, const char *subname)
{
	struct mmc_host *host = card->host;

	mq->card = card;

	mq->use_cqe = host->cqe_enabled;

	return mmc_mq_init(mq, card, lock);
}