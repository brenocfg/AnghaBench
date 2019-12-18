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
typedef  scalar_t__ u8 ;
struct qed_iwarp_ep {int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,struct qed_iwarp_cm_event_params*) ;int /*<<< orphan*/  list_entry; int /*<<< orphan*/  state; int /*<<< orphan*/  cm_info; int /*<<< orphan*/  qp; } ;
struct qed_iwarp_cm_event_params {int /*<<< orphan*/  status; int /*<<< orphan*/ * cm_info; struct qed_iwarp_ep* ep_context; int /*<<< orphan*/  event; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  iw_lock; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 scalar_t__ IWARP_QP_IN_ERROR_GOOD_CLOSE ; 
 int /*<<< orphan*/  QED_IWARP_EP_CLOSED ; 
 int /*<<< orphan*/  QED_IWARP_EVENT_CLOSE ; 
 int /*<<< orphan*/  QED_IWARP_QP_STATE_ERROR ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_iwarp_modify_qp (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_iwarp_cm_event_params*) ; 

__attribute__((used)) static void qed_iwarp_qp_in_error(struct qed_hwfn *p_hwfn,
				  struct qed_iwarp_ep *ep,
				  u8 fw_return_code)
{
	struct qed_iwarp_cm_event_params params;

	qed_iwarp_modify_qp(p_hwfn, ep->qp, QED_IWARP_QP_STATE_ERROR, true);

	params.event = QED_IWARP_EVENT_CLOSE;
	params.ep_context = ep;
	params.cm_info = &ep->cm_info;
	params.status = (fw_return_code == IWARP_QP_IN_ERROR_GOOD_CLOSE) ?
			 0 : -ECONNRESET;

	/* paired with READ_ONCE in destroy_qp */
	smp_store_release(&ep->state, QED_IWARP_EP_CLOSED);

	spin_lock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	list_del(&ep->list_entry);
	spin_unlock_bh(&p_hwfn->p_rdma_info->iwarp.iw_lock);

	ep->event_cb(ep->cb_context, &params);
}