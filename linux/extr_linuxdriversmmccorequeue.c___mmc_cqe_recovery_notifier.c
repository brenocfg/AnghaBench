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
struct mmc_queue {int recovery_needed; int /*<<< orphan*/  recovery_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __mmc_cqe_recovery_notifier(struct mmc_queue *mq)
{
	if (!mq->recovery_needed) {
		mq->recovery_needed = true;
		schedule_work(&mq->recovery_work);
	}
}