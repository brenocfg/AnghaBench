#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct cpl_rdma_terminate {int dummy; } ;
struct c4iw_qp_attributes {int /*<<< orphan*/  next_state; } ;
struct TYPE_7__ {TYPE_4__* qp; } ;
struct c4iw_ep {TYPE_3__ com; } ;
struct c4iw_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  qid; } ;
struct TYPE_6__ {TYPE_1__ sq; } ;
struct TYPE_8__ {int /*<<< orphan*/  rhp; TYPE_2__ wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  C4IW_QP_ATTR_NEXT_STATE ; 
 int /*<<< orphan*/  C4IW_QP_STATE_TERMINATE ; 
 unsigned int GET_TID (struct cpl_rdma_terminate*) ; 
 int /*<<< orphan*/  c4iw_modify_qp (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,struct c4iw_qp_attributes*,int) ; 
 int /*<<< orphan*/  c4iw_put_ep (TYPE_3__*) ; 
 struct cpl_rdma_terminate* cplhdr (struct sk_buff*) ; 
 struct c4iw_ep* get_ep_from_tid (struct c4iw_dev*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,...) ; 

__attribute__((used)) static int terminate(struct c4iw_dev *dev, struct sk_buff *skb)
{
	struct cpl_rdma_terminate *rpl = cplhdr(skb);
	unsigned int tid = GET_TID(rpl);
	struct c4iw_ep *ep;
	struct c4iw_qp_attributes attrs;

	ep = get_ep_from_tid(dev, tid);

	if (ep) {
		if (ep->com.qp) {
			pr_warn("TERM received tid %u qpid %u\n", tid,
				ep->com.qp->wq.sq.qid);
			attrs.next_state = C4IW_QP_STATE_TERMINATE;
			c4iw_modify_qp(ep->com.qp->rhp, ep->com.qp,
				       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		}

		c4iw_put_ep(&ep->com);
	} else
		pr_warn("TERM received tid %u no ep/qp\n", tid);

	return 0;
}