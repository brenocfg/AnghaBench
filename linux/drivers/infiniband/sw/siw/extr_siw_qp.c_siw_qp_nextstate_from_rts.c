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
struct siw_qp_attrs {int state; } ;
struct TYPE_3__ {int state; } ;
struct siw_qp {TYPE_1__ attrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  wr_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMAP_ECODE_UNSPECIFIED ; 
 int /*<<< orphan*/  RDMAP_ETYPE_CATASTROPHIC ; 
#define  SIW_QP_STATE_CLOSING 130 
#define  SIW_QP_STATE_ERROR 129 
#define  SIW_QP_STATE_TERMINATE 128 
 int /*<<< orphan*/  SIW_WR_IDLE ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_RDMAP ; 
 int /*<<< orphan*/  siw_init_terminate (struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siw_rq_flush (struct siw_qp*) ; 
 int /*<<< orphan*/  siw_sq_flush (struct siw_qp*) ; 
 TYPE_2__* tx_wqe (struct siw_qp*) ; 

__attribute__((used)) static int siw_qp_nextstate_from_rts(struct siw_qp *qp,
				     struct siw_qp_attrs *attrs)
{
	int drop_conn = 0;

	switch (attrs->state) {
	case SIW_QP_STATE_CLOSING:
		/*
		 * Verbs: move to IDLE if SQ and ORQ are empty.
		 * Move to ERROR otherwise. But first of all we must
		 * close the connection. So we keep CLOSING or ERROR
		 * as a transient state, schedule connection drop work
		 * and wait for the socket state change upcall to
		 * come back closed.
		 */
		if (tx_wqe(qp)->wr_status == SIW_WR_IDLE) {
			qp->attrs.state = SIW_QP_STATE_CLOSING;
		} else {
			qp->attrs.state = SIW_QP_STATE_ERROR;
			siw_sq_flush(qp);
		}
		siw_rq_flush(qp);

		drop_conn = 1;
		break;

	case SIW_QP_STATE_TERMINATE:
		qp->attrs.state = SIW_QP_STATE_TERMINATE;

		siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
				   RDMAP_ETYPE_CATASTROPHIC,
				   RDMAP_ECODE_UNSPECIFIED, 1);
		drop_conn = 1;
		break;

	case SIW_QP_STATE_ERROR:
		/*
		 * This is an emergency close.
		 *
		 * Any in progress transmit operation will get
		 * cancelled.
		 * This will likely result in a protocol failure,
		 * if a TX operation is in transit. The caller
		 * could unconditional wait to give the current
		 * operation a chance to complete.
		 * Esp., how to handle the non-empty IRQ case?
		 * The peer was asking for data transfer at a valid
		 * point in time.
		 */
		siw_sq_flush(qp);
		siw_rq_flush(qp);
		qp->attrs.state = SIW_QP_STATE_ERROR;
		drop_conn = 1;
		break;

	default:
		break;
	}
	return drop_conn;
}