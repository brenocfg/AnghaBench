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
struct siw_qp {TYPE_1__* ib_qp; int /*<<< orphan*/  qp_num; struct siw_device* sdev; int /*<<< orphan*/  ref; } ;
struct siw_device {int /*<<< orphan*/  qp_xa; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*) ; 
 int xa_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_32b ; 

int siw_qp_add(struct siw_device *sdev, struct siw_qp *qp)
{
	int rv = xa_alloc(&sdev->qp_xa, &qp->ib_qp->qp_num, qp, xa_limit_32b,
			  GFP_KERNEL);

	if (!rv) {
		kref_init(&qp->ref);
		qp->sdev = sdev;
		qp->qp_num = qp->ib_qp->qp_num;
		siw_dbg_qp(qp, "new QP\n");
	}
	return rv;
}