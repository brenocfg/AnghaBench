#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ureq ;
struct TYPE_5__ {int /*<<< orphan*/  num_pbes; } ;
struct TYPE_8__ {TYPE_2__* pbl_tbl; TYPE_1__ pbl_info; } ;
struct qedr_qp {int /*<<< orphan*/  qed_qp; int /*<<< orphan*/  icid; int /*<<< orphan*/  qp_id; TYPE_4__ urq; int /*<<< orphan*/  srq; TYPE_4__ usq; } ;
struct qedr_pd {int dummy; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_3__* ops; int /*<<< orphan*/  ibdev; } ;
struct qedr_create_qp_ureq {int /*<<< orphan*/  rq_pbl_ptr; int /*<<< orphan*/  rq_num_pages; int /*<<< orphan*/  sq_pbl_ptr; int /*<<< orphan*/  sq_num_pages; int /*<<< orphan*/  qp_handle_hi; int /*<<< orphan*/  qp_handle_lo; int /*<<< orphan*/  rq_len; int /*<<< orphan*/  rq_addr; int /*<<< orphan*/  sq_len; int /*<<< orphan*/  sq_addr; } ;
struct qed_rdma_create_qp_out_params {int /*<<< orphan*/  icid; int /*<<< orphan*/  qp_id; } ;
struct qed_rdma_create_qp_in_params {int /*<<< orphan*/  rq_pbl_ptr; int /*<<< orphan*/  rq_num_pages; int /*<<< orphan*/  sq_pbl_ptr; int /*<<< orphan*/  sq_num_pages; int /*<<< orphan*/  qp_handle_hi; int /*<<< orphan*/  qp_handle_lo; int /*<<< orphan*/  rq_len; int /*<<< orphan*/  rq_addr; int /*<<< orphan*/  sq_len; int /*<<< orphan*/  sq_addr; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_init_attr {int dummy; } ;
struct ib_pd {int dummy; } ;
typedef  int /*<<< orphan*/  in_params ;
struct TYPE_7__ {int (* rdma_destroy_qp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rdma_create_qp ) (int /*<<< orphan*/ ,struct qedr_create_qp_ureq*,struct qed_rdma_create_qp_out_params*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct qedr_pd* get_qedr_pd (struct ib_pd*) ; 
 int ib_copy_from_udata (struct qedr_create_qp_ureq*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  memset (struct qedr_create_qp_ureq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_cleanup_user (struct qedr_dev*,struct qedr_qp*) ; 
 int qedr_copy_qp_uresp (struct qedr_dev*,struct qedr_qp*,struct ib_udata*) ; 
 int /*<<< orphan*/  qedr_init_common_qp_in_params (struct qedr_dev*,struct qedr_pd*,struct qedr_qp*,struct ib_qp_init_attr*,int,struct qedr_create_qp_ureq*) ; 
 int qedr_init_user_queue (struct ib_udata*,struct qedr_dev*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_iwarp_populate_user_qp (struct qedr_dev*,struct qedr_qp*,struct qed_rdma_create_qp_out_params*) ; 
 int /*<<< orphan*/  qedr_qp_user_print (struct qedr_dev*,struct qedr_qp*) ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ *,int) ; 
 int rdma_protocol_roce (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qedr_create_qp_ureq*,struct qed_rdma_create_qp_out_params*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedr_create_user_qp(struct qedr_dev *dev,
			       struct qedr_qp *qp,
			       struct ib_pd *ibpd,
			       struct ib_udata *udata,
			       struct ib_qp_init_attr *attrs)
{
	struct qed_rdma_create_qp_in_params in_params;
	struct qed_rdma_create_qp_out_params out_params;
	struct qedr_pd *pd = get_qedr_pd(ibpd);
	struct qedr_create_qp_ureq ureq;
	int alloc_and_init = rdma_protocol_roce(&dev->ibdev, 1);
	int rc = -EINVAL;

	memset(&ureq, 0, sizeof(ureq));
	rc = ib_copy_from_udata(&ureq, udata, sizeof(ureq));
	if (rc) {
		DP_ERR(dev, "Problem copying data from user space\n");
		return rc;
	}

	/* SQ - read access only (0), dma sync not required (0) */
	rc = qedr_init_user_queue(udata, dev, &qp->usq, ureq.sq_addr,
				  ureq.sq_len, 0, 0, alloc_and_init);
	if (rc)
		return rc;

	if (!qp->srq) {
		/* RQ - read access only (0), dma sync not required (0) */
		rc = qedr_init_user_queue(udata, dev, &qp->urq, ureq.rq_addr,
					  ureq.rq_len, 0, 0, alloc_and_init);
		if (rc)
			return rc;
	}

	memset(&in_params, 0, sizeof(in_params));
	qedr_init_common_qp_in_params(dev, pd, qp, attrs, false, &in_params);
	in_params.qp_handle_lo = ureq.qp_handle_lo;
	in_params.qp_handle_hi = ureq.qp_handle_hi;
	in_params.sq_num_pages = qp->usq.pbl_info.num_pbes;
	in_params.sq_pbl_ptr = qp->usq.pbl_tbl->pa;
	if (!qp->srq) {
		in_params.rq_num_pages = qp->urq.pbl_info.num_pbes;
		in_params.rq_pbl_ptr = qp->urq.pbl_tbl->pa;
	}

	qp->qed_qp = dev->ops->rdma_create_qp(dev->rdma_ctx,
					      &in_params, &out_params);

	if (!qp->qed_qp) {
		rc = -ENOMEM;
		goto err1;
	}

	if (rdma_protocol_iwarp(&dev->ibdev, 1))
		qedr_iwarp_populate_user_qp(dev, qp, &out_params);

	qp->qp_id = out_params.qp_id;
	qp->icid = out_params.icid;

	rc = qedr_copy_qp_uresp(dev, qp, udata);
	if (rc)
		goto err;

	qedr_qp_user_print(dev, qp);

	return 0;
err:
	rc = dev->ops->rdma_destroy_qp(dev->rdma_ctx, qp->qed_qp);
	if (rc)
		DP_ERR(dev, "create qp: fatal fault. rc=%d", rc);

err1:
	qedr_cleanup_user(dev, qp);
	return rc;
}