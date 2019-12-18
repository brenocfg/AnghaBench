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
struct c4iw_ep {int /*<<< orphan*/  com; } ;
struct c4iw_dev {int /*<<< orphan*/  hwtids; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_get_ep (int /*<<< orphan*/ *) ; 
 struct c4iw_ep* xa_load (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct c4iw_ep *get_ep_from_tid(struct c4iw_dev *dev, unsigned int tid)
{
	struct c4iw_ep *ep;
	unsigned long flags;

	xa_lock_irqsave(&dev->hwtids, flags);
	ep = xa_load(&dev->hwtids, tid);
	if (ep)
		c4iw_get_ep(&ep->com);
	xa_unlock_irqrestore(&dev->hwtids, flags);
	return ep;
}