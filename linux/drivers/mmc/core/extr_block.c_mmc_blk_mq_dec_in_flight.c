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
struct request {int dummy; } ;
struct mmc_queue {int* in_flight; int /*<<< orphan*/  ctx; int /*<<< orphan*/  card; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t mmc_issue_type (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_put_card (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mmc_tot_in_flight (struct mmc_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mmc_blk_mq_dec_in_flight(struct mmc_queue *mq, struct request *req)
{
	unsigned long flags;
	bool put_card;

	spin_lock_irqsave(&mq->lock, flags);

	mq->in_flight[mmc_issue_type(mq, req)] -= 1;

	put_card = (mmc_tot_in_flight(mq) == 0);

	spin_unlock_irqrestore(&mq->lock, flags);

	if (put_card)
		mmc_put_card(mq->card, &mq->ctx);
}