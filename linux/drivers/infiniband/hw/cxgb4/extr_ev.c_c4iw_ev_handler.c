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
struct c4iw_dev {int /*<<< orphan*/  cqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct c4iw_cq {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  comp_handler_lock; TYPE_1__ ibcq; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_clear_cq_armed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 struct c4iw_cq* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int c4iw_ev_handler(struct c4iw_dev *dev, u32 qid)
{
	struct c4iw_cq *chp;
	unsigned long flag;

	xa_lock_irqsave(&dev->cqs, flag);
	chp = xa_load(&dev->cqs, qid);
	if (chp) {
		atomic_inc(&chp->refcnt);
		xa_unlock_irqrestore(&dev->cqs, flag);
		t4_clear_cq_armed(&chp->cq);
		spin_lock_irqsave(&chp->comp_handler_lock, flag);
		(*chp->ibcq.comp_handler)(&chp->ibcq, chp->ibcq.cq_context);
		spin_unlock_irqrestore(&chp->comp_handler_lock, flag);
		if (atomic_dec_and_test(&chp->refcnt))
			wake_up(&chp->wait);
	} else {
		pr_debug("unknown cqid 0x%x\n", qid);
		xa_unlock_irqrestore(&dev->cqs, flag);
	}
	return 0;
}