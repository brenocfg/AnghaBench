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
typedef  scalar_t__ u32 ;
struct nes_timer_entry {scalar_t__ skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_id; } ;
struct nes_qp {int /*<<< orphan*/  refcount; TYPE_1__ hwqp; int /*<<< orphan*/  lock; int /*<<< orphan*/  ibqp_state; int /*<<< orphan*/  last_aeq; int /*<<< orphan*/  hw_tcp_state; scalar_t__ cm_id; } ;
struct nes_cm_node {struct nes_timer_entry* recv_entry; struct iw_cm_id* cm_id; int /*<<< orphan*/  cm_core; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  NES_AEQE_AEID_RESET_SENT ; 
 int /*<<< orphan*/  NES_AEQE_TCP_STATE_CLOSED ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nes_timer_entry*) ; 
 int /*<<< orphan*/  nes_cm_disconn (struct nes_qp*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct iw_cm_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem_ref_cm_node (int /*<<< orphan*/ ,struct nes_cm_node*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 

__attribute__((used)) static void handle_recv_entry(struct nes_cm_node *cm_node, u32 rem_node)
{
	struct nes_timer_entry *recv_entry = cm_node->recv_entry;
	struct iw_cm_id *cm_id = cm_node->cm_id;
	struct nes_qp *nesqp;
	unsigned long qplockflags;

	if (!recv_entry)
		return;
	nesqp = (struct nes_qp *)recv_entry->skb;
	if (nesqp) {
		spin_lock_irqsave(&nesqp->lock, qplockflags);
		if (nesqp->cm_id) {
			nes_debug(NES_DBG_CM, "QP%u: cm_id = %p, "
				  "refcount = %d: HIT A "
				  "NES_TIMER_TYPE_CLOSE with something "
				  "to do!!!\n", nesqp->hwqp.qp_id, cm_id,
				  atomic_read(&nesqp->refcount));
			nesqp->hw_tcp_state = NES_AEQE_TCP_STATE_CLOSED;
			nesqp->last_aeq = NES_AEQE_AEID_RESET_SENT;
			nesqp->ibqp_state = IB_QPS_ERR;
			spin_unlock_irqrestore(&nesqp->lock, qplockflags);
			nes_cm_disconn(nesqp);
		} else {
			spin_unlock_irqrestore(&nesqp->lock, qplockflags);
			nes_debug(NES_DBG_CM, "QP%u: cm_id = %p, "
				  "refcount = %d: HIT A "
				  "NES_TIMER_TYPE_CLOSE with nothing "
				  "to do!!!\n", nesqp->hwqp.qp_id, cm_id,
				  atomic_read(&nesqp->refcount));
		}
	} else if (rem_node) {
		/* TIME_WAIT state */
		rem_ref_cm_node(cm_node->cm_core, cm_node);
	}
	if (cm_node->cm_id)
		cm_id->rem_ref(cm_id);
	kfree(recv_entry);
	cm_node->recv_entry = NULL;
}