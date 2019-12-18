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
struct hwq {int /*<<< orphan*/  hrrq_slock; int /*<<< orphan*/  irqpoll; int /*<<< orphan*/  hrrq_online; struct afu* afu; } ;
struct afu {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ afu_is_irqpoll_enabled (struct afu*) ; 
 int /*<<< orphan*/  doneq ; 
 int /*<<< orphan*/  irq_poll_sched (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_cmd_doneq (int /*<<< orphan*/ *) ; 
 int process_hrrq (struct hwq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t cxlflash_rrq_irq(int irq, void *data)
{
	struct hwq *hwq = (struct hwq *)data;
	struct afu *afu = hwq->afu;
	unsigned long hrrq_flags;
	LIST_HEAD(doneq);
	int num_entries = 0;

	spin_lock_irqsave(&hwq->hrrq_slock, hrrq_flags);

	/* Silently drop spurious interrupts when queue is not online */
	if (!hwq->hrrq_online) {
		spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);
		return IRQ_HANDLED;
	}

	if (afu_is_irqpoll_enabled(afu)) {
		irq_poll_sched(&hwq->irqpoll);
		spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);
		return IRQ_HANDLED;
	}

	num_entries = process_hrrq(hwq, &doneq, -1);
	spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);

	if (num_entries == 0)
		return IRQ_NONE;

	process_cmd_doneq(&doneq);
	return IRQ_HANDLED;
}