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
struct rvt_qp {size_t state; int s_flags; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  r_ack_psn; int /*<<< orphan*/  s_ack_psn; int /*<<< orphan*/  r_nak_state; int /*<<< orphan*/  s_nak_state; } ;
struct hfi1_packet {int /*<<< orphan*/  rcd; struct rvt_qp* qp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rc_qacks; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;

/* Variables and functions */
 int RVT_PROCESS_RECV_OK ; 
 int RVT_S_ACK_PENDING ; 
 int RVT_S_ECN ; 
 int RVT_S_RESP_PENDING ; 
 int /*<<< orphan*/  hfi1_schedule_send (struct rvt_qp*) ; 
 int* ib_rvt_state_ops ; 
 struct hfi1_ibport* rcd_to_iport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hfi1_queue_rc_ack(struct hfi1_packet *packet, bool is_fecn)
{
	struct rvt_qp *qp = packet->qp;
	struct hfi1_ibport *ibp;
	unsigned long flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	if (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		goto unlock;
	ibp = rcd_to_iport(packet->rcd);
	this_cpu_inc(*ibp->rvp.rc_qacks);
	qp->s_flags |= RVT_S_ACK_PENDING | RVT_S_RESP_PENDING;
	qp->s_nak_state = qp->r_nak_state;
	qp->s_ack_psn = qp->r_ack_psn;
	if (is_fecn)
		qp->s_flags |= RVT_S_ECN;

	/* Schedule the send tasklet. */
	hfi1_schedule_send(qp);
unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
}