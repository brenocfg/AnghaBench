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
struct rvt_qp {int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_iowait (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_tid_rdma_flush_wait (struct rvt_qp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void flush_qp_waiters(struct rvt_qp *qp)
{
	lockdep_assert_held(&qp->s_lock);
	flush_iowait(qp);
	hfi1_tid_rdma_flush_wait(qp);
}