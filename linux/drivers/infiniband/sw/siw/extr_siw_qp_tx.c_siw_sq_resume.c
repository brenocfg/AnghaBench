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
struct TYPE_4__ {int /*<<< orphan*/  tx_suspend; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct siw_qp {int /*<<< orphan*/  state_lock; TYPE_2__ tx_ctx; TYPE_1__ attrs; } ;

/* Variables and functions */
 scalar_t__ SIW_QP_STATE_RTS ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,...) ; 
 int /*<<< orphan*/  siw_qp_cm_drop (struct siw_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_qp_put (struct siw_qp*) ; 
 int siw_qp_sq_process (struct siw_qp*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_sq_resume(struct siw_qp *qp)
{
	if (down_read_trylock(&qp->state_lock)) {
		if (likely(qp->attrs.state == SIW_QP_STATE_RTS &&
			   !qp->tx_ctx.tx_suspend)) {
			int rv = siw_qp_sq_process(qp);

			up_read(&qp->state_lock);

			if (unlikely(rv < 0)) {
				siw_dbg_qp(qp, "SQ task failed: err %d\n", rv);

				if (!qp->tx_ctx.tx_suspend)
					siw_qp_cm_drop(qp, 0);
			}
		} else {
			up_read(&qp->state_lock);
		}
	} else {
		siw_dbg_qp(qp, "Resume SQ while QP locked\n");
	}
	siw_qp_put(qp);
}