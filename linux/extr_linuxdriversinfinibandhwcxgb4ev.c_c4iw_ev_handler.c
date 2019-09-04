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
typedef  int /*<<< orphan*/  u32 ;
struct c4iw_dev {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct c4iw_cq {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  comp_handler_lock; TYPE_1__ ibcq; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct c4iw_cq* get_chp (struct c4iw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_clear_cq_armed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int c4iw_ev_handler(struct c4iw_dev *dev, u32 qid)
{
	struct c4iw_cq *chp;
	unsigned long flag;

	spin_lock_irqsave(&dev->lock, flag);
	chp = get_chp(dev, qid);
	if (chp) {
		atomic_inc(&chp->refcnt);
		spin_unlock_irqrestore(&dev->lock, flag);
		t4_clear_cq_armed(&chp->cq);
		spin_lock_irqsave(&chp->comp_handler_lock, flag);
		(*chp->ibcq.comp_handler)(&chp->ibcq, chp->ibcq.cq_context);
		spin_unlock_irqrestore(&chp->comp_handler_lock, flag);
		if (atomic_dec_and_test(&chp->refcnt))
			wake_up(&chp->wait);
	} else {
		pr_debug("unknown cqid 0x%x\n", qid);
		spin_unlock_irqrestore(&dev->lock, flag);
	}
	return 0;
}