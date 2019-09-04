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
struct qedr_qp {TYPE_2__* dev; int /*<<< orphan*/  qp_id; int /*<<< orphan*/  refcnt; } ;
struct ib_qp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct TYPE_4__ {TYPE_1__ qpidr; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct qedr_qp* get_qedr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qedr_qp*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void qedr_iw_qp_rem_ref(struct ib_qp *ibqp)
{
	struct qedr_qp *qp = get_qedr_qp(ibqp);

	if (atomic_dec_and_test(&qp->refcnt)) {
		spin_lock_irq(&qp->dev->qpidr.idr_lock);
		idr_remove(&qp->dev->qpidr.idr, qp->qp_id);
		spin_unlock_irq(&qp->dev->qpidr.idr_lock);
		kfree(qp);
	}
}