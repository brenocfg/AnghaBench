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
struct rxe_send_wqe {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct rxe_qp {TYPE_1__ sq; int /*<<< orphan*/  resp_pkts; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  advance_consumer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_complete (struct rxe_qp*,struct rxe_send_wqe*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rxe_send_wqe* queue_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxe_drain_resp_pkts(struct rxe_qp *qp, bool notify)
{
	struct sk_buff *skb;
	struct rxe_send_wqe *wqe;

	while ((skb = skb_dequeue(&qp->resp_pkts))) {
		rxe_drop_ref(qp);
		kfree_skb(skb);
	}

	while ((wqe = queue_head(qp->sq.queue))) {
		if (notify) {
			wqe->status = IB_WC_WR_FLUSH_ERR;
			do_complete(qp, wqe);
		} else {
			advance_consumer(qp->sq.queue);
		}
	}
}