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
struct siw_qp {int /*<<< orphan*/  state_lock; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_rq_flush (struct siw_qp*) ; 
 struct siw_qp* to_siw_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void siw_verbs_rq_flush(struct ib_qp *base_qp)
{
	struct siw_qp *qp = to_siw_qp(base_qp);

	down_write(&qp->state_lock);
	siw_rq_flush(qp);
	up_write(&qp->state_lock);
}