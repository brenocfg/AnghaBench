#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* last; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_6__ {int /*<<< orphan*/  queue_lock; TYPE_1__* queue; } ;
typedef  TYPE_2__ isdn_net_dev ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __inline__ void isdn_net_add_to_bundle(isdn_net_dev *nd, isdn_net_local *nlp)
{
	isdn_net_local *lp;
	unsigned long flags;

	spin_lock_irqsave(&nd->queue_lock, flags);

	lp = nd->queue;
//	printk(KERN_DEBUG "%s: lp:%s(%p) nlp:%s(%p) last(%p)\n",
//		__func__, lp->name, lp, nlp->name, nlp, lp->last);
	nlp->last = lp->last;
	lp->last->next = nlp;
	lp->last = nlp;
	nlp->next = lp;
	nd->queue = nlp;

	spin_unlock_irqrestore(&nd->queue_lock, flags);
}