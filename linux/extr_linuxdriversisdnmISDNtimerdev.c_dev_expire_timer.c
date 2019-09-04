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
typedef  int /*<<< orphan*/  u_long ;
struct timer_list {int dummy; } ;
struct mISDNtimer {scalar_t__ id; TYPE_1__* dev; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  expired; } ;

/* Variables and functions */
 struct mISDNtimer* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mISDNtimer* timer ; 
 int /*<<< orphan*/  tl ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dev_expire_timer(struct timer_list *t)
{
	struct mISDNtimer *timer = from_timer(timer, t, tl);
	u_long			flags;

	spin_lock_irqsave(&timer->dev->lock, flags);
	if (timer->id >= 0)
		list_move_tail(&timer->list, &timer->dev->expired);
	wake_up_interruptible(&timer->dev->wait);
	spin_unlock_irqrestore(&timer->dev->lock, flags);
}