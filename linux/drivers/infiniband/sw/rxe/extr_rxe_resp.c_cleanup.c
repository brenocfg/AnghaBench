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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct rxe_qp* mr; } ;
struct rxe_qp {TYPE_1__ resp; int /*<<< orphan*/  req_pkts; } ;
struct rxe_pkt_info {int dummy; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
 int RESPST_DONE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum resp_states cleanup(struct rxe_qp *qp,
				struct rxe_pkt_info *pkt)
{
	struct sk_buff *skb;

	if (pkt) {
		skb = skb_dequeue(&qp->req_pkts);
		rxe_drop_ref(qp);
		kfree_skb(skb);
	}

	if (qp->resp.mr) {
		rxe_drop_ref(qp->resp.mr);
		qp->resp.mr = NULL;
	}

	return RESPST_DONE;
}