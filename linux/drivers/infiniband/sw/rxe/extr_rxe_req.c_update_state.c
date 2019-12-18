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
struct rxe_send_wqe {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wqe_index; int /*<<< orphan*/  opcode; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
struct rxe_qp {scalar_t__ qp_timeout_jiffies; int /*<<< orphan*/  retrans_timer; scalar_t__ need_req_skb; TYPE_2__ req; TYPE_1__ sq; } ;
struct rxe_pkt_info {int mask; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int RXE_END_MASK ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  next_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_state(struct rxe_qp *qp, struct rxe_send_wqe *wqe,
			 struct rxe_pkt_info *pkt, int payload)
{
	qp->req.opcode = pkt->opcode;

	if (pkt->mask & RXE_END_MASK)
		qp->req.wqe_index = next_index(qp->sq.queue, qp->req.wqe_index);

	qp->need_req_skb = 0;

	if (qp->qp_timeout_jiffies && !timer_pending(&qp->retrans_timer))
		mod_timer(&qp->retrans_timer,
			  jiffies + qp->qp_timeout_jiffies);
}