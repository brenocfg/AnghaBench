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
struct TYPE_2__ {int head; int n; int /*<<< orphan*/  lock; } ;
struct qcom_slim_ctrl {struct completion** wr_comp; TYPE_1__ tx; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void slim_ack_txn(struct qcom_slim_ctrl *ctrl, int err)
{
	struct completion *comp;
	unsigned long flags;
	int idx;

	spin_lock_irqsave(&ctrl->tx.lock, flags);
	idx = ctrl->tx.head;
	ctrl->tx.head = (ctrl->tx.head + 1) % ctrl->tx.n;
	spin_unlock_irqrestore(&ctrl->tx.lock, flags);

	comp = ctrl->wr_comp[idx];
	ctrl->wr_comp[idx] = NULL;

	complete(comp);
}