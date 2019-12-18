#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ib_qp {int qp_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_wr; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_wr; } ;
struct qedr_qp {void* rqe_wr_id; struct ib_qp ibqp; void* wqe_wr_id; TYPE_3__ sq; TYPE_2__ rq; } ;
struct qedr_dev {TYPE_5__* gsi_rqcq; TYPE_4__* ndev; int /*<<< orphan*/  gsi_ll2_mac_address; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_wr; } ;
struct ib_qp_init_attr {TYPE_1__ cap; } ;
struct TYPE_10__ {void* cq_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,struct qedr_qp*) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 int ENOMEM ; 
 struct ib_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* QEDR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  QEDR_MSG_GSI ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int qedr_check_gsi_qp_attrs (struct qedr_dev*,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  qedr_destroy_gsi_cq (struct qedr_dev*,struct ib_qp_init_attr*) ; 
 int qedr_ll2_start (struct qedr_dev*,struct ib_qp_init_attr*,struct qedr_qp*) ; 
 int qedr_ll2_stop (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_store_gsi_qp_cq (struct qedr_dev*,struct qedr_qp*,struct ib_qp_init_attr*) ; 

struct ib_qp *qedr_create_gsi_qp(struct qedr_dev *dev,
				 struct ib_qp_init_attr *attrs,
				 struct qedr_qp *qp)
{
	int rc;

	rc = qedr_check_gsi_qp_attrs(dev, attrs);
	if (rc)
		return ERR_PTR(rc);

	rc = qedr_ll2_start(dev, attrs, qp);
	if (rc) {
		DP_ERR(dev, "create gsi qp: failed on ll2 start. rc=%d\n", rc);
		return ERR_PTR(rc);
	}

	/* create QP */
	qp->ibqp.qp_num = 1;
	qp->rq.max_wr = attrs->cap.max_recv_wr;
	qp->sq.max_wr = attrs->cap.max_send_wr;

	qp->rqe_wr_id = kcalloc(qp->rq.max_wr, sizeof(*qp->rqe_wr_id),
				GFP_KERNEL);
	if (!qp->rqe_wr_id)
		goto err;
	qp->wqe_wr_id = kcalloc(qp->sq.max_wr, sizeof(*qp->wqe_wr_id),
				GFP_KERNEL);
	if (!qp->wqe_wr_id)
		goto err;

	qedr_store_gsi_qp_cq(dev, qp, attrs);
	ether_addr_copy(dev->gsi_ll2_mac_address, dev->ndev->dev_addr);

	/* the GSI CQ is handled by the driver so remove it from the FW */
	qedr_destroy_gsi_cq(dev, attrs);
	dev->gsi_rqcq->cq_type = QEDR_CQ_TYPE_GSI;
	dev->gsi_rqcq->cq_type = QEDR_CQ_TYPE_GSI;

	DP_DEBUG(dev, QEDR_MSG_GSI, "created GSI QP %p\n", qp);

	return &qp->ibqp;

err:
	kfree(qp->rqe_wr_id);

	rc = qedr_ll2_stop(dev);
	if (rc)
		DP_ERR(dev, "create gsi qp: failed destroy on create\n");

	return ERR_PTR(-ENOMEM);
}