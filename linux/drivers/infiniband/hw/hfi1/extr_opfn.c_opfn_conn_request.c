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
typedef  int /*<<< orphan*/  wr ;
typedef  int u64 ;
typedef  int u16 ;
struct rvt_qp {int /*<<< orphan*/  ibqp; struct hfi1_qp_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
struct ib_atomic_wr {int compare_add; TYPE_2__ wr; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_3__ {int requested; int completed; int curr; int /*<<< orphan*/  lock; int /*<<< orphan*/  extended; } ;
struct hfi1_qp_priv {TYPE_1__ opfn; } ;
struct hfi1_opfn_type {int /*<<< orphan*/  (* request ) (struct rvt_qp*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_VERBS_E_ATOMIC_VADDR ; 
 int /*<<< orphan*/  IB_WR_OPFN ; 
 int OPFN_CODE (int) ; 
 int STL_VERBS_EXTD_MAX ; 
 int STL_VERBS_EXTD_NONE ; 
 struct hfi1_opfn_type* hfi1_opfn_handlers ; 
 int ib_post_send (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  memset (struct ib_atomic_wr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opfn_schedule_conn_request (struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rvt_qp*,int*) ; 
 int /*<<< orphan*/  trace_hfi1_msg_opfn_conn_request (struct rvt_qp*,char*,int) ; 
 int /*<<< orphan*/  trace_hfi1_opfn_data_conn_request (struct rvt_qp*,int,int) ; 
 int /*<<< orphan*/  trace_hfi1_opfn_state_conn_request (struct rvt_qp*) ; 

__attribute__((used)) static void opfn_conn_request(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct ib_atomic_wr wr;
	u16 mask, capcode;
	struct hfi1_opfn_type *extd;
	u64 data;
	unsigned long flags;
	int ret = 0;

	trace_hfi1_opfn_state_conn_request(qp);
	spin_lock_irqsave(&priv->opfn.lock, flags);
	/*
	 * Exit if the extended bit is not set, or if nothing is requested, or
	 * if we have completed all requests, or if a previous request is in
	 * progress
	 */
	if (!priv->opfn.extended || !priv->opfn.requested ||
	    priv->opfn.requested == priv->opfn.completed || priv->opfn.curr)
		goto done;

	mask = priv->opfn.requested & ~priv->opfn.completed;
	capcode = ilog2(mask & ~(mask - 1)) + 1;
	if (capcode >= STL_VERBS_EXTD_MAX) {
		priv->opfn.completed |= OPFN_CODE(capcode);
		goto done;
	}

	extd = &hfi1_opfn_handlers[capcode];
	if (!extd || !extd->request || !extd->request(qp, &data)) {
		/*
		 * Either there is no handler for this capability or the request
		 * packet could not be generated. Either way, mark it as done so
		 * we don't keep attempting to complete it.
		 */
		priv->opfn.completed |= OPFN_CODE(capcode);
		goto done;
	}

	trace_hfi1_opfn_data_conn_request(qp, capcode, data);
	data = (data & ~0xf) | capcode;

	memset(&wr, 0, sizeof(wr));
	wr.wr.opcode = IB_WR_OPFN;
	wr.remote_addr = HFI1_VERBS_E_ATOMIC_VADDR;
	wr.compare_add = data;

	priv->opfn.curr = capcode;	/* A new request is now in progress */
	/* Drop opfn.lock before calling ib_post_send() */
	spin_unlock_irqrestore(&priv->opfn.lock, flags);

	ret = ib_post_send(&qp->ibqp, &wr.wr, NULL);
	if (ret)
		goto err;
	trace_hfi1_opfn_state_conn_request(qp);
	return;
err:
	trace_hfi1_msg_opfn_conn_request(qp, "ib_ost_send failed: ret = ",
					 (u64)ret);
	spin_lock_irqsave(&priv->opfn.lock, flags);
	/*
	 * In case of an unexpected error return from ib_post_send
	 * clear opfn.curr and reschedule to try again
	 */
	priv->opfn.curr = STL_VERBS_EXTD_NONE;
	opfn_schedule_conn_request(qp);
done:
	spin_unlock_irqrestore(&priv->opfn.lock, flags);
}