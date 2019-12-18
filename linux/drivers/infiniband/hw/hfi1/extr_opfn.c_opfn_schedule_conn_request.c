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
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  opfn_work; } ;
struct hfi1_qp_priv {TYPE_1__ opfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  opfn_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hfi1_opfn_state_sched_conn_request (struct rvt_qp*) ; 

__attribute__((used)) static void opfn_schedule_conn_request(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;

	trace_hfi1_opfn_state_sched_conn_request(qp);
	queue_work(opfn_wq, &priv->opfn.opfn_work);
}