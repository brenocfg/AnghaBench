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
struct qedr_qp {int /*<<< orphan*/  qp_id; TYPE_1__* dev; int /*<<< orphan*/  refcnt; } ;
struct ib_qp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qps; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct qedr_qp* get_qedr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  kfree (struct qedr_qp*) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qedr_iw_qp_rem_ref(struct ib_qp *ibqp)
{
	struct qedr_qp *qp = get_qedr_qp(ibqp);

	if (atomic_dec_and_test(&qp->refcnt)) {
		xa_erase_irq(&qp->dev->qps, qp->qp_id);
		kfree(qp);
	}
}