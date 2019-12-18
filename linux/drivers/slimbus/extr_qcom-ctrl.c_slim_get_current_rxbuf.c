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
struct TYPE_2__ {int tail; int head; int sl_sz; int n; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct qcom_slim_ctrl {TYPE_1__ rx; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int slim_get_current_rxbuf(struct qcom_slim_ctrl *ctrl, void *buf)
{
	unsigned long flags;

	spin_lock_irqsave(&ctrl->rx.lock, flags);
	if (ctrl->rx.tail == ctrl->rx.head) {
		spin_unlock_irqrestore(&ctrl->rx.lock, flags);
		return -ENODATA;
	}
	memcpy(buf, ctrl->rx.base + (ctrl->rx.head * ctrl->rx.sl_sz),
				ctrl->rx.sl_sz);

	ctrl->rx.head = (ctrl->rx.head + 1) % ctrl->rx.n;
	spin_unlock_irqrestore(&ctrl->rx.lock, flags);

	return 0;
}