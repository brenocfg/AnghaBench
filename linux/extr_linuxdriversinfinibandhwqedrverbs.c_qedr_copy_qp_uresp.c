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
typedef  int /*<<< orphan*/  uresp ;
struct qedr_qp {int /*<<< orphan*/  icid; int /*<<< orphan*/  qp_id; } ;
struct qedr_dev {scalar_t__ atomic_cap; } ;
struct qedr_create_qp_uresp {int atomic_supported; int /*<<< orphan*/  qp_id; } ;
struct ib_udata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IB_ATOMIC_NONE ; 
 int /*<<< orphan*/  memset (struct qedr_create_qp_uresp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_copy_rq_uresp (struct qedr_dev*,struct qedr_create_qp_uresp*,struct qedr_qp*) ; 
 int /*<<< orphan*/  qedr_copy_sq_uresp (struct qedr_dev*,struct qedr_create_qp_uresp*,struct qedr_qp*) ; 
 int qedr_ib_copy_to_udata (struct ib_udata*,struct qedr_create_qp_uresp*,int) ; 

__attribute__((used)) static int qedr_copy_qp_uresp(struct qedr_dev *dev,
			      struct qedr_qp *qp, struct ib_udata *udata)
{
	struct qedr_create_qp_uresp uresp;
	int rc;

	memset(&uresp, 0, sizeof(uresp));
	qedr_copy_sq_uresp(dev, &uresp, qp);
	qedr_copy_rq_uresp(dev, &uresp, qp);

	uresp.atomic_supported = dev->atomic_cap != IB_ATOMIC_NONE;
	uresp.qp_id = qp->qp_id;

	rc = qedr_ib_copy_to_udata(udata, &uresp, sizeof(uresp));
	if (rc)
		DP_ERR(dev,
		       "create qp: failed a copy to user space with qp icid=0x%x.\n",
		       qp->icid);

	return rc;
}