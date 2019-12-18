#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t state; int /*<<< orphan*/ * sk; } ;
struct TYPE_6__ {int tx_suspend; } ;
struct TYPE_5__ {int rx_suspend; } ;
struct siw_qp {TYPE_3__ attrs; int /*<<< orphan*/  state_lock; int /*<<< orphan*/ * cep; TYPE_2__ tx_ctx; TYPE_1__ rx_stream; } ;
struct TYPE_8__ {int /*<<< orphan*/  wr_status; } ;

/* Variables and functions */
#define  SIW_QP_STATE_CLOSING 132 
 void* SIW_QP_STATE_ERROR ; 
#define  SIW_QP_STATE_IDLE 131 
#define  SIW_QP_STATE_RTR 130 
#define  SIW_QP_STATE_RTS 129 
#define  SIW_QP_STATE_TERMINATE 128 
 int /*<<< orphan*/  SIW_WR_IDLE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_cep_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * siw_qp_state_to_string ; 
 int /*<<< orphan*/  siw_rq_flush (struct siw_qp*) ; 
 int /*<<< orphan*/  siw_sq_flush (struct siw_qp*) ; 
 TYPE_4__* tx_wqe (struct siw_qp*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void siw_qp_llp_close(struct siw_qp *qp)
{
	siw_dbg_qp(qp, "enter llp close, state = %s\n",
		   siw_qp_state_to_string[qp->attrs.state]);

	down_write(&qp->state_lock);

	qp->rx_stream.rx_suspend = 1;
	qp->tx_ctx.tx_suspend = 1;
	qp->attrs.sk = NULL;

	switch (qp->attrs.state) {
	case SIW_QP_STATE_RTS:
	case SIW_QP_STATE_RTR:
	case SIW_QP_STATE_IDLE:
	case SIW_QP_STATE_TERMINATE:
		qp->attrs.state = SIW_QP_STATE_ERROR;
		break;
	/*
	 * SIW_QP_STATE_CLOSING:
	 *
	 * This is a forced close. shall the QP be moved to
	 * ERROR or IDLE ?
	 */
	case SIW_QP_STATE_CLOSING:
		if (tx_wqe(qp)->wr_status == SIW_WR_IDLE)
			qp->attrs.state = SIW_QP_STATE_ERROR;
		else
			qp->attrs.state = SIW_QP_STATE_IDLE;
		break;

	default:
		siw_dbg_qp(qp, "llp close: no state transition needed: %s\n",
			   siw_qp_state_to_string[qp->attrs.state]);
		break;
	}
	siw_sq_flush(qp);
	siw_rq_flush(qp);

	/*
	 * Dereference closing CEP
	 */
	if (qp->cep) {
		siw_cep_put(qp->cep);
		qp->cep = NULL;
	}

	up_write(&qp->state_lock);

	siw_dbg_qp(qp, "llp close exit: state %s\n",
		   siw_qp_state_to_string[qp->attrs.state]);
}