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
struct ib_cq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* iw_cq_request_notification ) (struct i40iw_cq_uk*,int) ;} ;
struct i40iw_cq_uk {TYPE_2__ ops; } ;
struct TYPE_3__ {struct i40iw_cq_uk cq_uk; } ;
struct i40iw_cq {int /*<<< orphan*/  lock; TYPE_1__ sc_cq; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;
typedef  enum i40iw_completion_notify { ____Placeholder_i40iw_completion_notify } i40iw_completion_notify ;

/* Variables and functions */
 int IB_CQ_SOLICITED ; 
 int IW_CQ_COMPL_EVENT ; 
 int IW_CQ_COMPL_SOLICITED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct i40iw_cq_uk*,int) ; 

__attribute__((used)) static int i40iw_req_notify_cq(struct ib_cq *ibcq,
			       enum ib_cq_notify_flags notify_flags)
{
	struct i40iw_cq *iwcq;
	struct i40iw_cq_uk *ukcq;
	unsigned long flags;
	enum i40iw_completion_notify cq_notify = IW_CQ_COMPL_EVENT;

	iwcq = (struct i40iw_cq *)ibcq;
	ukcq = &iwcq->sc_cq.cq_uk;
	if (notify_flags == IB_CQ_SOLICITED)
		cq_notify = IW_CQ_COMPL_SOLICITED;
	spin_lock_irqsave(&iwcq->lock, flags);
	ukcq->ops.iw_cq_request_notification(ukcq, cq_notify);
	spin_unlock_irqrestore(&iwcq->lock, flags);
	return 0;
}