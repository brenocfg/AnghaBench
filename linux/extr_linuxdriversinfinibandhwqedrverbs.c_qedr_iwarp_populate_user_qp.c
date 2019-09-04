#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pbl_info; TYPE_3__* pbl_tbl; int /*<<< orphan*/  umem; } ;
struct TYPE_4__ {int /*<<< orphan*/  pbl_info; TYPE_3__* pbl_tbl; int /*<<< orphan*/  umem; } ;
struct qedr_qp {TYPE_2__ urq; int /*<<< orphan*/  srq; TYPE_1__ usq; } ;
struct qedr_dev {int dummy; } ;
struct qed_rdma_create_qp_out_params {int /*<<< orphan*/  rq_pbl_phys; int /*<<< orphan*/  rq_pbl_virt; int /*<<< orphan*/  sq_pbl_phys; int /*<<< orphan*/  sq_pbl_virt; } ;
struct TYPE_6__ {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PAGE_SHIFT ; 
 int /*<<< orphan*/  qedr_populate_pbls (struct qedr_dev*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qedr_iwarp_populate_user_qp(struct qedr_dev *dev,
			    struct qedr_qp *qp,
			    struct qed_rdma_create_qp_out_params *out_params)
{
	qp->usq.pbl_tbl->va = out_params->sq_pbl_virt;
	qp->usq.pbl_tbl->pa = out_params->sq_pbl_phys;

	qedr_populate_pbls(dev, qp->usq.umem, qp->usq.pbl_tbl,
			   &qp->usq.pbl_info, FW_PAGE_SHIFT);
	if (!qp->srq) {
		qp->urq.pbl_tbl->va = out_params->rq_pbl_virt;
		qp->urq.pbl_tbl->pa = out_params->rq_pbl_phys;
	}

	qedr_populate_pbls(dev, qp->urq.umem, qp->urq.pbl_tbl,
			   &qp->urq.pbl_info, FW_PAGE_SHIFT);
}