#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ wq_pidx_inc; } ;
struct TYPE_6__ {scalar_t__ wq_pidx_inc; } ;
struct TYPE_7__ {TYPE_1__ rq; TYPE_2__ sq; } ;
struct c4iw_qp {int /*<<< orphan*/  lock; TYPE_3__ wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_ring_rq_db (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_ring_sq_db (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resume_rc_qp(struct c4iw_qp *qp)
{
	spin_lock(&qp->lock);
	t4_ring_sq_db(&qp->wq, qp->wq.sq.wq_pidx_inc, NULL);
	qp->wq.sq.wq_pidx_inc = 0;
	t4_ring_rq_db(&qp->wq, qp->wq.rq.wq_pidx_inc, NULL);
	qp->wq.rq.wq_pidx_inc = 0;
	spin_unlock(&qp->lock);
}