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
struct ena_com_admin_queue {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  outstanding_cmds; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_POLL_MS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ena_com_wait_for_abort_completion(struct ena_com_dev *ena_dev)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	unsigned long flags = 0;

	spin_lock_irqsave(&admin_queue->q_lock, flags);
	while (atomic_read(&admin_queue->outstanding_cmds) != 0) {
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);
		msleep(ENA_POLL_MS);
		spin_lock_irqsave(&admin_queue->q_lock, flags);
	}
	spin_unlock_irqrestore(&admin_queue->q_lock, flags);
}