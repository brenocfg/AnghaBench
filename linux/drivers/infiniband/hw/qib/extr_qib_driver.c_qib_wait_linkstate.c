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
typedef  int u32 ;
struct qib_pportdata {int state_wanted; int lflags; int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  state_wait; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int qib_wait_linkstate(struct qib_pportdata *ppd, u32 state, int msecs)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	if (ppd->state_wanted) {
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		ret = -EBUSY;
		goto bail;
	}
	ppd->state_wanted = state;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	wait_event_interruptible_timeout(ppd->state_wait,
					 (ppd->lflags & state),
					 msecs_to_jiffies(msecs));
	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->state_wanted = 0;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);

	if (!(ppd->lflags & state))
		ret = -ETIMEDOUT;
	else
		ret = 0;
bail:
	return ret;
}