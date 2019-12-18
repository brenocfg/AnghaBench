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
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_6__ {int tx_suspend; } ;
struct TYPE_5__ {int rx_suspend; } ;
struct siw_qp {TYPE_3__ term_info; struct siw_cep* cep; TYPE_2__ tx_ctx; TYPE_1__ rx_stream; } ;
struct siw_cep {scalar_t__ state; int /*<<< orphan*/ * qp; int /*<<< orphan*/ * sock; TYPE_4__* cm_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* rem_ref ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IW_CM_EVENT_CLOSE ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REPLY ; 
 int /*<<< orphan*/  SIW_CM_WORK_CLOSE_LLP ; 
#define  SIW_EPSTATE_AWAIT_MPAREP 135 
#define  SIW_EPSTATE_AWAIT_MPAREQ 134 
#define  SIW_EPSTATE_CLOSED 133 
#define  SIW_EPSTATE_CONNECTING 132 
#define  SIW_EPSTATE_IDLE 131 
#define  SIW_EPSTATE_LISTENING 130 
#define  SIW_EPSTATE_RDMA_MODE 129 
#define  SIW_EPSTATE_RECVD_MPAREQ 128 
 int /*<<< orphan*/  siw_cep_put (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_free (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cep_set_inuse (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cm_queue_work (struct siw_cep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_cm_upcall (struct siw_cep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,...) ; 
 int /*<<< orphan*/  siw_qp_put (struct siw_qp*) ; 
 int /*<<< orphan*/  siw_send_terminate (struct siw_qp*) ; 
 int /*<<< orphan*/  siw_socket_disassoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void siw_qp_cm_drop(struct siw_qp *qp, int schedule)
{
	struct siw_cep *cep = qp->cep;

	qp->rx_stream.rx_suspend = 1;
	qp->tx_ctx.tx_suspend = 1;

	if (!qp->cep)
		return;

	if (schedule) {
		siw_cm_queue_work(cep, SIW_CM_WORK_CLOSE_LLP);
	} else {
		siw_cep_set_inuse(cep);

		if (cep->state == SIW_EPSTATE_CLOSED) {
			siw_dbg_cep(cep, "already closed\n");
			goto out;
		}
		siw_dbg_cep(cep, "immediate close, state %d\n", cep->state);

		if (qp->term_info.valid)
			siw_send_terminate(qp);

		if (cep->cm_id) {
			switch (cep->state) {
			case SIW_EPSTATE_AWAIT_MPAREP:
				siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY,
					      -EINVAL);
				break;

			case SIW_EPSTATE_RDMA_MODE:
				siw_cm_upcall(cep, IW_CM_EVENT_CLOSE, 0);
				break;

			case SIW_EPSTATE_IDLE:
			case SIW_EPSTATE_LISTENING:
			case SIW_EPSTATE_CONNECTING:
			case SIW_EPSTATE_AWAIT_MPAREQ:
			case SIW_EPSTATE_RECVD_MPAREQ:
			case SIW_EPSTATE_CLOSED:
			default:
				break;
			}
			cep->cm_id->rem_ref(cep->cm_id);
			cep->cm_id = NULL;
			siw_cep_put(cep);
		}
		cep->state = SIW_EPSTATE_CLOSED;

		if (cep->sock) {
			siw_socket_disassoc(cep->sock);
			/*
			 * Immediately close socket
			 */
			sock_release(cep->sock);
			cep->sock = NULL;
		}
		if (cep->qp) {
			cep->qp = NULL;
			siw_qp_put(qp);
		}
out:
		siw_cep_set_free(cep);
	}
}