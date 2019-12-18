#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dev; } ;
struct c4iw_ep {TYPE_2__ com; int /*<<< orphan*/  hwtid; } ;
struct TYPE_3__ {int /*<<< orphan*/  hwtids; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 scalar_t__ xa_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void remove_ep_tid(struct c4iw_ep *ep)
{
	unsigned long flags;

	xa_lock_irqsave(&ep->com.dev->hwtids, flags);
	__xa_erase(&ep->com.dev->hwtids, ep->hwtid);
	if (xa_empty(&ep->com.dev->hwtids))
		wake_up(&ep->com.dev->wait);
	xa_unlock_irqrestore(&ep->com.dev->hwtids, flags);
}