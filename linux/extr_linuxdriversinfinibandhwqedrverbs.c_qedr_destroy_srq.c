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
struct qedr_srq {int /*<<< orphan*/  srq_id; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; int /*<<< orphan*/  srqidr; } ;
struct qed_rdma_destroy_srq_in_params {int /*<<< orphan*/  srq_id; } ;
struct ib_srq {TYPE_2__* pd; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {scalar_t__ uobject; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rdma_destroy_srq ) (int /*<<< orphan*/ ,struct qed_rdma_destroy_srq_in_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDR_MSG_SRQ ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_srq* get_qedr_srq (struct ib_srq*) ; 
 int /*<<< orphan*/  kfree (struct qedr_srq*) ; 
 int /*<<< orphan*/  qedr_free_srq_kernel_params (struct qedr_srq*) ; 
 int /*<<< orphan*/  qedr_free_srq_user_params (struct qedr_srq*) ; 
 int /*<<< orphan*/  qedr_idr_remove (struct qedr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_rdma_destroy_srq_in_params*) ; 

int qedr_destroy_srq(struct ib_srq *ibsrq)
{
	struct qed_rdma_destroy_srq_in_params in_params = {};
	struct qedr_dev *dev = get_qedr_dev(ibsrq->device);
	struct qedr_srq *srq = get_qedr_srq(ibsrq);

	qedr_idr_remove(dev, &dev->srqidr, srq->srq_id);
	in_params.srq_id = srq->srq_id;
	dev->ops->rdma_destroy_srq(dev->rdma_ctx, &in_params);

	if (ibsrq->pd->uobject)
		qedr_free_srq_user_params(srq);
	else
		qedr_free_srq_kernel_params(srq);

	DP_DEBUG(dev, QEDR_MSG_SRQ,
		 "destroy srq: destroyed srq with srq_id=0x%0x\n",
		 srq->srq_id);
	kfree(srq);

	return 0;
}