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
struct rxe_send_wqe {scalar_t__ last_psn; scalar_t__ state; int mask; } ;
struct TYPE_2__ {scalar_t__ psn; } ;
struct rxe_qp {TYPE_1__ comp; } ;
struct rxe_pkt_info {scalar_t__ psn; } ;
typedef  scalar_t__ s32 ;
typedef  enum comp_state { ____Placeholder_comp_state } comp_state ;

/* Variables and functions */
 int COMPST_CHECK_ACK ; 
 int COMPST_COMP_ACK ; 
 int COMPST_COMP_WQE ; 
 int COMPST_DONE ; 
 int COMPST_ERROR_RETRY ; 
 int WR_ATOMIC_OR_READ_MASK ; 
 scalar_t__ psn_compare (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reset_retry_counters (struct rxe_qp*) ; 
 scalar_t__ wqe_state_pending ; 

__attribute__((used)) static inline enum comp_state check_psn(struct rxe_qp *qp,
					struct rxe_pkt_info *pkt,
					struct rxe_send_wqe *wqe)
{
	s32 diff;

	/* check to see if response is past the oldest WQE. if it is, complete
	 * send/write or error read/atomic
	 */
	diff = psn_compare(pkt->psn, wqe->last_psn);
	if (diff > 0) {
		if (wqe->state == wqe_state_pending) {
			if (wqe->mask & WR_ATOMIC_OR_READ_MASK)
				return COMPST_ERROR_RETRY;

			reset_retry_counters(qp);
			return COMPST_COMP_WQE;
		} else {
			return COMPST_DONE;
		}
	}

	/* compare response packet to expected response */
	diff = psn_compare(pkt->psn, qp->comp.psn);
	if (diff < 0) {
		/* response is most likely a retried packet if it matches an
		 * uncompleted WQE go complete it else ignore it
		 */
		if (pkt->psn == wqe->last_psn)
			return COMPST_COMP_ACK;
		else
			return COMPST_DONE;
	} else if ((diff > 0) && (wqe->mask & WR_ATOMIC_OR_READ_MASK)) {
		return COMPST_DONE;
	} else {
		return COMPST_CHECK_ACK;
	}
}