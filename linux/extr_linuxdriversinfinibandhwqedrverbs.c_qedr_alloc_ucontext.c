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
typedef  int /*<<< orphan*/  uresp ;
struct ib_ucontext {int dummy; } ;
struct qedr_ucontext {struct ib_ucontext ibucontext; int /*<<< orphan*/  dpi_size; int /*<<< orphan*/  dpi_phys_addr; struct qedr_dev* dev; int /*<<< orphan*/  mm_list_lock; int /*<<< orphan*/  mm_head; int /*<<< orphan*/  dpi_addr; int /*<<< orphan*/  dpi; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_rqe; int /*<<< orphan*/  max_sqe; } ;
struct qedr_dev {TYPE_2__ attr; int /*<<< orphan*/  user_dpm_enabled; int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; } ;
struct qedr_alloc_ucontext_resp {int wids_enabled; int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  sges_per_srq_wr; int /*<<< orphan*/  sges_per_recv_wr; int /*<<< orphan*/  sges_per_send_wr; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  db_size; int /*<<< orphan*/  db_pa; int /*<<< orphan*/  wid_count; int /*<<< orphan*/  dpm_enabled; } ;
struct qed_rdma_add_user_out_params {int /*<<< orphan*/  wid_count; int /*<<< orphan*/  dpi_size; int /*<<< orphan*/  dpi_phys_addr; int /*<<< orphan*/  dpi_addr; int /*<<< orphan*/  dpi; } ;
struct ib_udata {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int (* rdma_add_user ) (int /*<<< orphan*/ ,struct qed_rdma_add_user_out_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,struct ib_ucontext*) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 int EFAULT ; 
 int ENOMEM ; 
 struct ib_ucontext* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QEDR_MAX_CQES ; 
 int /*<<< orphan*/  QEDR_MAX_RQE_ELEMENTS_PER_RQE ; 
 int /*<<< orphan*/  QEDR_MAX_SQE_ELEMENTS_PER_SQE ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  kfree (struct qedr_ucontext*) ; 
 struct qedr_ucontext* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qedr_alloc_ucontext_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int qedr_add_mmap (struct qedr_ucontext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qedr_ib_copy_to_udata (struct ib_udata*,struct qedr_alloc_ucontext_resp*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_rdma_add_user_out_params*) ; 

struct ib_ucontext *qedr_alloc_ucontext(struct ib_device *ibdev,
					struct ib_udata *udata)
{
	int rc;
	struct qedr_ucontext *ctx;
	struct qedr_alloc_ucontext_resp uresp;
	struct qedr_dev *dev = get_qedr_dev(ibdev);
	struct qed_rdma_add_user_out_params oparams;

	if (!udata)
		return ERR_PTR(-EFAULT);

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	rc = dev->ops->rdma_add_user(dev->rdma_ctx, &oparams);
	if (rc) {
		DP_ERR(dev,
		       "failed to allocate a DPI for a new RoCE application, rc=%d. To overcome this consider to increase the number of DPIs, increase the doorbell BAR size or just close unnecessary RoCE applications. In order to increase the number of DPIs consult the qedr readme\n",
		       rc);
		goto err;
	}

	ctx->dpi = oparams.dpi;
	ctx->dpi_addr = oparams.dpi_addr;
	ctx->dpi_phys_addr = oparams.dpi_phys_addr;
	ctx->dpi_size = oparams.dpi_size;
	INIT_LIST_HEAD(&ctx->mm_head);
	mutex_init(&ctx->mm_list_lock);

	memset(&uresp, 0, sizeof(uresp));

	uresp.dpm_enabled = dev->user_dpm_enabled;
	uresp.wids_enabled = 1;
	uresp.wid_count = oparams.wid_count;
	uresp.db_pa = ctx->dpi_phys_addr;
	uresp.db_size = ctx->dpi_size;
	uresp.max_send_wr = dev->attr.max_sqe;
	uresp.max_recv_wr = dev->attr.max_rqe;
	uresp.max_srq_wr = dev->attr.max_srq_wr;
	uresp.sges_per_send_wr = QEDR_MAX_SQE_ELEMENTS_PER_SQE;
	uresp.sges_per_recv_wr = QEDR_MAX_RQE_ELEMENTS_PER_RQE;
	uresp.sges_per_srq_wr = dev->attr.max_srq_sge;
	uresp.max_cqes = QEDR_MAX_CQES;

	rc = qedr_ib_copy_to_udata(udata, &uresp, sizeof(uresp));
	if (rc)
		goto err;

	ctx->dev = dev;

	rc = qedr_add_mmap(ctx, ctx->dpi_phys_addr, ctx->dpi_size);
	if (rc)
		goto err;

	DP_DEBUG(dev, QEDR_MSG_INIT, "Allocating user context %p\n",
		 &ctx->ibucontext);
	return &ctx->ibucontext;

err:
	kfree(ctx);
	return ERR_PTR(rc);
}