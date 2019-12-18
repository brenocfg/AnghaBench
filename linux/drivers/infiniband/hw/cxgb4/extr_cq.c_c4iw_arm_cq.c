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
struct ib_cq {int dummy; } ;
struct c4iw_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  cq; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;

/* Variables and functions */
 int IB_CQ_REPORT_MISSED_EVENTS ; 
 int IB_CQ_SOLICITED ; 
 int IB_CQ_SOLICITED_MASK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  t4_arm_cq (int /*<<< orphan*/ *,int) ; 
 int t4_cq_notempty (int /*<<< orphan*/ *) ; 
 struct c4iw_cq* to_c4iw_cq (struct ib_cq*) ; 

int c4iw_arm_cq(struct ib_cq *ibcq, enum ib_cq_notify_flags flags)
{
	struct c4iw_cq *chp;
	int ret = 0;
	unsigned long flag;

	chp = to_c4iw_cq(ibcq);
	spin_lock_irqsave(&chp->lock, flag);
	t4_arm_cq(&chp->cq,
		  (flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED);
	if (flags & IB_CQ_REPORT_MISSED_EVENTS)
		ret = t4_cq_notempty(&chp->cq);
	spin_unlock_irqrestore(&chp->lock, flag);
	return ret;
}