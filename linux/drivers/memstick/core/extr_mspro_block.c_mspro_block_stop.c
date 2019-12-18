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
struct mspro_block_data {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  block_req; } ;
struct memstick_dev {int /*<<< orphan*/  mrq_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_stop_hw_queues (int /*<<< orphan*/ ) ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mspro_block_stop(struct memstick_dev *card)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	int rc = 0;
	unsigned long flags;

	while (1) {
		spin_lock_irqsave(&msb->q_lock, flags);
		if (!msb->block_req) {
			blk_mq_stop_hw_queues(msb->queue);
			rc = 1;
		}
		spin_unlock_irqrestore(&msb->q_lock, flags);

		if (rc)
			break;

		wait_for_completion(&card->mrq_complete);
	}
}