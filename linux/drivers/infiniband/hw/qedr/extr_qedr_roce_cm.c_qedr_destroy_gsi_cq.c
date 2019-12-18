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
struct qedr_dev {int /*<<< orphan*/  cdev; TYPE_2__* ops; int /*<<< orphan*/  rdma_ctx; } ;
struct qedr_cq {scalar_t__ icid; int /*<<< orphan*/  pbl; } ;
struct qed_rdma_destroy_cq_out_params {int dummy; } ;
struct qed_rdma_destroy_cq_in_params {scalar_t__ icid; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct TYPE_4__ {TYPE_1__* common; int /*<<< orphan*/  (* rdma_destroy_cq ) (int /*<<< orphan*/ ,struct qed_rdma_destroy_cq_in_params*,struct qed_rdma_destroy_cq_out_params*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct qedr_cq* get_qedr_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_rdma_destroy_cq_in_params*,struct qed_rdma_destroy_cq_out_params*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct qed_rdma_destroy_cq_in_params*,struct qed_rdma_destroy_cq_out_params*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedr_destroy_gsi_cq(struct qedr_dev *dev,
				struct ib_qp_init_attr *attrs)
{
	struct qed_rdma_destroy_cq_in_params iparams;
	struct qed_rdma_destroy_cq_out_params oparams;
	struct qedr_cq *cq;

	cq = get_qedr_cq(attrs->send_cq);
	iparams.icid = cq->icid;
	dev->ops->rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
	dev->ops->common->chain_free(dev->cdev, &cq->pbl);

	cq = get_qedr_cq(attrs->recv_cq);
	/* if a dedicated recv_cq was used, delete it too */
	if (iparams.icid != cq->icid) {
		iparams.icid = cq->icid;
		dev->ops->rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);
		dev->ops->common->chain_free(dev->cdev, &cq->pbl);
	}
}