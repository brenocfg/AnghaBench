#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ureq ;
typedef  void* u64 ;
typedef  void* u32 ;
struct qedr_ucontext {int dummy; } ;
struct qed_chain {int dummy; } ;
struct qedr_srq_hwq_info {void* phy_prod_pair_addr; struct qed_chain pbl; int /*<<< orphan*/  max_sges; int /*<<< orphan*/  max_wr; } ;
struct ib_srq {int dummy; } ;
struct TYPE_10__ {void* num_pbes; } ;
struct TYPE_13__ {TYPE_5__* umem; TYPE_4__* pbl_tbl; TYPE_3__ pbl_info; } ;
struct qedr_srq {int /*<<< orphan*/  srq_id; struct ib_srq ibsrq; TYPE_6__ usrq; int /*<<< orphan*/  lock; struct qedr_srq_hwq_info hw_srq; struct qedr_dev* dev; } ;
struct qedr_pd {int /*<<< orphan*/  pd_id; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_7__* ops; int /*<<< orphan*/  srqidr; } ;
struct qedr_create_srq_ureq {int dummy; } ;
struct qed_rdma_destroy_srq_in_params {int /*<<< orphan*/  srq_id; } ;
struct qed_rdma_create_srq_out_params {int /*<<< orphan*/  srq_id; } ;
struct qed_rdma_create_srq_in_params {void* page_size; void* num_pages; void* prod_pair_addr; void* pbl_base_addr; int /*<<< orphan*/  pd_id; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct ib_srq_init_attr {TYPE_1__ attr; } ;
struct ib_pd {TYPE_2__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_14__ {int (* rdma_create_srq ) (int /*<<< orphan*/ ,struct qed_rdma_create_srq_in_params*,struct qed_rdma_create_srq_out_params*) ;int /*<<< orphan*/  (* rdma_destroy_srq ) (int /*<<< orphan*/ ,struct qed_rdma_destroy_srq_in_params*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  page_shift; } ;
struct TYPE_11__ {void* pa; } ;
struct TYPE_9__ {struct ib_ucontext* context; } ;

/* Variables and functions */
 void* BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*) ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_srq* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDR_MSG_QP ; 
 int /*<<< orphan*/  QEDR_MSG_SRQ ; 
 void* QED_CHAIN_PAGE_SIZE ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_pd* get_qedr_pd (struct ib_pd*) ; 
 struct qedr_ucontext* get_qedr_ucontext (struct ib_ucontext*) ; 
 scalar_t__ ib_copy_from_udata (struct qedr_create_srq_ureq*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  kfree (struct qedr_srq*) ; 
 struct qedr_srq* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* qed_chain_get_page_cnt (struct qed_chain*) ; 
 void* qed_chain_get_pbl_phys (struct qed_chain*) ; 
 int qedr_alloc_srq_kernel_params (struct qedr_srq*,struct qedr_dev*,struct ib_srq_init_attr*) ; 
 int qedr_check_srq_params (struct ib_pd*,struct qedr_dev*,struct ib_srq_init_attr*,struct ib_udata*) ; 
 int qedr_copy_srq_uresp (struct qedr_dev*,struct qedr_srq*,struct ib_udata*) ; 
 int /*<<< orphan*/  qedr_free_srq_kernel_params (struct qedr_srq*) ; 
 int /*<<< orphan*/  qedr_free_srq_user_params (struct qedr_srq*) ; 
 int qedr_idr_add (struct qedr_dev*,int /*<<< orphan*/ *,struct qedr_srq*,int /*<<< orphan*/ ) ; 
 int qedr_init_srq_user_params (struct ib_ucontext*,struct qedr_srq*,struct qedr_create_srq_ureq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_rdma_create_srq_in_params*,struct qed_rdma_create_srq_out_params*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct qed_rdma_destroy_srq_in_params*) ; 

struct ib_srq *qedr_create_srq(struct ib_pd *ibpd,
			       struct ib_srq_init_attr *init_attr,
			       struct ib_udata *udata)
{
	struct qed_rdma_destroy_srq_in_params destroy_in_params;
	struct qed_rdma_create_srq_in_params in_params = {};
	struct qedr_dev *dev = get_qedr_dev(ibpd->device);
	struct qed_rdma_create_srq_out_params out_params;
	struct qedr_pd *pd = get_qedr_pd(ibpd);
	struct qedr_create_srq_ureq ureq = {};
	u64 pbl_base_addr, phy_prod_pair_addr;
	struct ib_ucontext *ib_ctx = NULL;
	struct qedr_srq_hwq_info *hw_srq;
	struct qedr_ucontext *ctx = NULL;
	u32 page_cnt, page_size;
	struct qedr_srq *srq;
	int rc = 0;

	DP_DEBUG(dev, QEDR_MSG_QP,
		 "create SRQ called from %s (pd %p)\n",
		 (udata) ? "User lib" : "kernel", pd);

	rc = qedr_check_srq_params(ibpd, dev, init_attr, udata);
	if (rc)
		return ERR_PTR(-EINVAL);

	srq = kzalloc(sizeof(*srq), GFP_KERNEL);
	if (!srq)
		return ERR_PTR(-ENOMEM);

	srq->dev = dev;
	hw_srq = &srq->hw_srq;
	spin_lock_init(&srq->lock);

	hw_srq->max_wr = init_attr->attr.max_wr;
	hw_srq->max_sges = init_attr->attr.max_sge;

	if (udata && ibpd->uobject && ibpd->uobject->context) {
		ib_ctx = ibpd->uobject->context;
		ctx = get_qedr_ucontext(ib_ctx);

		if (ib_copy_from_udata(&ureq, udata, sizeof(ureq))) {
			DP_ERR(dev,
			       "create srq: problem copying data from user space\n");
			goto err0;
		}

		rc = qedr_init_srq_user_params(ib_ctx, srq, &ureq, 0, 0);
		if (rc)
			goto err0;

		page_cnt = srq->usrq.pbl_info.num_pbes;
		pbl_base_addr = srq->usrq.pbl_tbl->pa;
		phy_prod_pair_addr = hw_srq->phy_prod_pair_addr;
		page_size = BIT(srq->usrq.umem->page_shift);
	} else {
		struct qed_chain *pbl;

		rc = qedr_alloc_srq_kernel_params(srq, dev, init_attr);
		if (rc)
			goto err0;

		pbl = &hw_srq->pbl;
		page_cnt = qed_chain_get_page_cnt(pbl);
		pbl_base_addr = qed_chain_get_pbl_phys(pbl);
		phy_prod_pair_addr = hw_srq->phy_prod_pair_addr;
		page_size = QED_CHAIN_PAGE_SIZE;
	}

	in_params.pd_id = pd->pd_id;
	in_params.pbl_base_addr = pbl_base_addr;
	in_params.prod_pair_addr = phy_prod_pair_addr;
	in_params.num_pages = page_cnt;
	in_params.page_size = page_size;

	rc = dev->ops->rdma_create_srq(dev->rdma_ctx, &in_params, &out_params);
	if (rc)
		goto err1;

	srq->srq_id = out_params.srq_id;

	if (udata) {
		rc = qedr_copy_srq_uresp(dev, srq, udata);
		if (rc)
			goto err2;
	}

	rc = qedr_idr_add(dev, &dev->srqidr, srq, srq->srq_id);
	if (rc)
		goto err2;

	DP_DEBUG(dev, QEDR_MSG_SRQ,
		 "create srq: created srq with srq_id=0x%0x\n", srq->srq_id);
	return &srq->ibsrq;

err2:
	destroy_in_params.srq_id = srq->srq_id;

	dev->ops->rdma_destroy_srq(dev->rdma_ctx, &destroy_in_params);
err1:
	if (udata)
		qedr_free_srq_user_params(srq);
	else
		qedr_free_srq_kernel_params(srq);
err0:
	kfree(srq);

	return ERR_PTR(-EFAULT);
}