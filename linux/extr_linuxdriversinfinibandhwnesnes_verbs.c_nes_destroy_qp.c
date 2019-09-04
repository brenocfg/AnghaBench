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
struct nes_ucontext {size_t first_free_wq; int /*<<< orphan*/ ** mmap_nesqp; int /*<<< orphan*/  allocated_wqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  qp_id; } ;
struct nes_qp {int destroyed; scalar_t__ ibqp_state; size_t mmap_sq_db_index; scalar_t__ nesscq; scalar_t__ nesrcq; int /*<<< orphan*/  ibqp; int /*<<< orphan*/  page; scalar_t__ sq_kmapped; scalar_t__ pbl_pbase; scalar_t__ user_mode; int /*<<< orphan*/  refcount; TYPE_1__ hwqp; struct iw_cm_id* cm_id; } ;
struct iw_cm_id {int (* event_handler ) (struct iw_cm_id*,struct iw_cm_event*) ;int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct iw_cm_event {scalar_t__ private_data_len; int /*<<< orphan*/ * private_data; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  status; int /*<<< orphan*/  event; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {TYPE_2__* uobject; } ;
struct TYPE_4__ {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  IB_QPS_ERR ; 
 scalar_t__ IB_QPS_INIT ; 
 scalar_t__ IB_QPS_RTR ; 
 scalar_t__ IB_QPS_RTS ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REPLY ; 
 int /*<<< orphan*/  NES_DBG_QP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_clean_cq (struct nes_qp*,scalar_t__) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  nes_modify_qp (int /*<<< orphan*/ *,struct ib_qp_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_rem_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 int stub2 (struct iw_cm_id*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  sw_qps_destroyed ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 
 struct nes_ucontext* to_nesucontext (scalar_t__) ; 

__attribute__((used)) static int nes_destroy_qp(struct ib_qp *ibqp)
{
	struct nes_qp *nesqp = to_nesqp(ibqp);
	struct nes_ucontext *nes_ucontext;
	struct ib_qp_attr attr;
	struct iw_cm_id *cm_id;
	struct iw_cm_event cm_event;
	int ret = 0;

	atomic_inc(&sw_qps_destroyed);
	nesqp->destroyed = 1;

	/* Blow away the connection if it exists. */
	if (nesqp->ibqp_state >= IB_QPS_INIT && nesqp->ibqp_state <= IB_QPS_RTS) {
		/* if (nesqp->ibqp_state == IB_QPS_RTS) { */
		attr.qp_state = IB_QPS_ERR;
		nes_modify_qp(&nesqp->ibqp, &attr, IB_QP_STATE, NULL);
	}

	if (((nesqp->ibqp_state == IB_QPS_INIT) ||
			(nesqp->ibqp_state == IB_QPS_RTR)) && (nesqp->cm_id)) {
		cm_id = nesqp->cm_id;
		cm_event.event = IW_CM_EVENT_CONNECT_REPLY;
		cm_event.status = -ETIMEDOUT;
		cm_event.local_addr = cm_id->local_addr;
		cm_event.remote_addr = cm_id->remote_addr;
		cm_event.private_data = NULL;
		cm_event.private_data_len = 0;

		nes_debug(NES_DBG_QP, "Generating a CM Timeout Event for "
				"QP%u. cm_id = %p, refcount = %u. \n",
				nesqp->hwqp.qp_id, cm_id, atomic_read(&nesqp->refcount));

		cm_id->rem_ref(cm_id);
		ret = cm_id->event_handler(cm_id, &cm_event);
		if (ret)
			nes_debug(NES_DBG_QP, "OFA CM event_handler returned, ret=%d\n", ret);
	}

	if (nesqp->user_mode) {
		if ((ibqp->uobject)&&(ibqp->uobject->context)) {
			nes_ucontext = to_nesucontext(ibqp->uobject->context);
			clear_bit(nesqp->mmap_sq_db_index, nes_ucontext->allocated_wqs);
			nes_ucontext->mmap_nesqp[nesqp->mmap_sq_db_index] = NULL;
			if (nes_ucontext->first_free_wq > nesqp->mmap_sq_db_index) {
				nes_ucontext->first_free_wq = nesqp->mmap_sq_db_index;
			}
		}
		if (nesqp->pbl_pbase && nesqp->sq_kmapped) {
			nesqp->sq_kmapped = 0;
			kunmap(nesqp->page);
		}
	} else {
		/* Clean any pending completions from the cq(s) */
		if (nesqp->nesscq)
			nes_clean_cq(nesqp, nesqp->nesscq);

		if ((nesqp->nesrcq) && (nesqp->nesrcq != nesqp->nesscq))
			nes_clean_cq(nesqp, nesqp->nesrcq);
	}
	nes_rem_ref(&nesqp->ibqp);
	return 0;
}