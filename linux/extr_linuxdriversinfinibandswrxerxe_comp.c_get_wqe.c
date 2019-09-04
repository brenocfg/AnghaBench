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
struct rxe_send_wqe {scalar_t__ state; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct rxe_qp {TYPE_1__ sq; } ;
struct rxe_pkt_info {int dummy; } ;
typedef  enum comp_state { ____Placeholder_comp_state } comp_state ;

/* Variables and functions */
 int COMPST_CHECK_PSN ; 
 int COMPST_COMP_WQE ; 
 int COMPST_DONE ; 
 int COMPST_ERROR ; 
 int COMPST_EXIT ; 
 struct rxe_send_wqe* queue_head (int /*<<< orphan*/ ) ; 
 scalar_t__ wqe_state_done ; 
 scalar_t__ wqe_state_error ; 
 scalar_t__ wqe_state_posted ; 

__attribute__((used)) static inline enum comp_state get_wqe(struct rxe_qp *qp,
				      struct rxe_pkt_info *pkt,
				      struct rxe_send_wqe **wqe_p)
{
	struct rxe_send_wqe *wqe;

	/* we come here whether or not we found a response packet to see if
	 * there are any posted WQEs
	 */
	wqe = queue_head(qp->sq.queue);
	*wqe_p = wqe;

	/* no WQE or requester has not started it yet */
	if (!wqe || wqe->state == wqe_state_posted)
		return pkt ? COMPST_DONE : COMPST_EXIT;

	/* WQE does not require an ack */
	if (wqe->state == wqe_state_done)
		return COMPST_COMP_WQE;

	/* WQE caused an error */
	if (wqe->state == wqe_state_error)
		return COMPST_ERROR;

	/* we have a WQE, if we also have an ack check its PSN */
	return pkt ? COMPST_CHECK_PSN : COMPST_EXIT;
}