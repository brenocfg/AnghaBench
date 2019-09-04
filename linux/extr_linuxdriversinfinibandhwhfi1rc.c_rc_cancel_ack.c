#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rvt_qp {int /*<<< orphan*/  r_flags; int /*<<< orphan*/  rspwait; scalar_t__ r_adefered; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_R_RSP_NAK ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 

__attribute__((used)) static inline void rc_cancel_ack(struct rvt_qp *qp)
{
	qp->r_adefered = 0;
	if (list_empty(&qp->rspwait))
		return;
	list_del_init(&qp->rspwait);
	qp->r_flags &= ~RVT_R_RSP_NAK;
	rvt_put_qp(qp);
}