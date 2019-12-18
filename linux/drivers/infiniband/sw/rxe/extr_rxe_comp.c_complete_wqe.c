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
struct rxe_send_wqe {scalar_t__ state; int last_psn; } ;
struct TYPE_3__ {int /*<<< orphan*/  task; scalar_t__ wait_psn; } ;
struct TYPE_4__ {int psn; int opcode; } ;
struct rxe_qp {TYPE_1__ req; TYPE_2__ comp; } ;
struct rxe_pkt_info {int dummy; } ;
typedef  enum comp_state { ____Placeholder_comp_state } comp_state ;

/* Variables and functions */
 int BTH_PSN_MASK ; 
 int COMPST_GET_WQE ; 
 int /*<<< orphan*/  do_complete (struct rxe_qp*,struct rxe_send_wqe*) ; 
 scalar_t__ psn_compare (int,int) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 scalar_t__ wqe_state_pending ; 

__attribute__((used)) static inline enum comp_state complete_wqe(struct rxe_qp *qp,
					   struct rxe_pkt_info *pkt,
					   struct rxe_send_wqe *wqe)
{
	if (pkt && wqe->state == wqe_state_pending) {
		if (psn_compare(wqe->last_psn, qp->comp.psn) >= 0) {
			qp->comp.psn = (wqe->last_psn + 1) & BTH_PSN_MASK;
			qp->comp.opcode = -1;
		}

		if (qp->req.wait_psn) {
			qp->req.wait_psn = 0;
			rxe_run_task(&qp->req.task, 1);
		}
	}

	do_complete(qp, wqe);

	return COMPST_GET_WQE;
}