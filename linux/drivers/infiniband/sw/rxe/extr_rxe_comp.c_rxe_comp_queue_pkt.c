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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  task; } ;
struct rxe_qp {TYPE_1__ comp; int /*<<< orphan*/  resp_pkts; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxe; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXE_CNT_COMPLETER_SCHED ; 
 TYPE_2__* SKB_TO_PKT (struct sk_buff*) ; 
 int /*<<< orphan*/  rxe_counter_inc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void rxe_comp_queue_pkt(struct rxe_qp *qp, struct sk_buff *skb)
{
	int must_sched;

	skb_queue_tail(&qp->resp_pkts, skb);

	must_sched = skb_queue_len(&qp->resp_pkts) > 1;
	if (must_sched != 0)
		rxe_counter_inc(SKB_TO_PKT(skb)->rxe, RXE_CNT_COMPLETER_SCHED);

	rxe_run_task(&qp->comp.task, must_sched);
}