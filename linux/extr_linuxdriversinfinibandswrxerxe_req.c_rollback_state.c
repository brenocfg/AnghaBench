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
typedef  int /*<<< orphan*/  u32 ;
struct rxe_send_wqe {int /*<<< orphan*/  last_psn; int /*<<< orphan*/  first_psn; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  psn; } ;
struct rxe_qp {TYPE_1__ req; } ;

/* Variables and functions */

__attribute__((used)) static void rollback_state(struct rxe_send_wqe *wqe,
			   struct rxe_qp *qp,
			   struct rxe_send_wqe *rollback_wqe,
			   u32 rollback_psn)
{
	wqe->state     = rollback_wqe->state;
	wqe->first_psn = rollback_wqe->first_psn;
	wqe->last_psn  = rollback_wqe->last_psn;
	qp->req.psn    = rollback_psn;
}