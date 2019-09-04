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
struct qed_rdma_qp {int /*<<< orphan*/  icid; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  kfree (struct qed_rdma_qp*) ; 
 int qed_iwarp_destroy_qp (struct qed_hwfn*,struct qed_rdma_qp*) ; 
 int qed_roce_destroy_qp (struct qed_hwfn*,struct qed_rdma_qp*) ; 

__attribute__((used)) static int qed_rdma_destroy_qp(void *rdma_cxt, struct qed_rdma_qp *qp)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	int rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	if (QED_IS_IWARP_PERSONALITY(p_hwfn))
		rc = qed_iwarp_destroy_qp(p_hwfn, qp);
	else
		rc = qed_roce_destroy_qp(p_hwfn, qp);

	/* free qp params struct */
	kfree(qp);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP destroyed\n");
	return rc;
}