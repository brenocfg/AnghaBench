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
struct qedr_pd {int /*<<< orphan*/  pd_id; } ;
struct TYPE_9__ {int itid; int key; int local_read; int mw_bind; int zbva; int phy_mr; int dma_mr; scalar_t__ vaddr; scalar_t__ length; scalar_t__ fbo; int /*<<< orphan*/  pbl_page_size_log; int /*<<< orphan*/  pbl_two_level; scalar_t__ pbl_ptr; scalar_t__ remote_atomic; scalar_t__ remote_write; scalar_t__ remote_read; scalar_t__ local_write; int /*<<< orphan*/  pd; int /*<<< orphan*/  tid_type; } ;
struct TYPE_7__ {int lkey; int rkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  pbl_size; int /*<<< orphan*/  two_layered; } ;
struct TYPE_10__ {TYPE_1__ pbl_info; } ;
struct qedr_mr {TYPE_4__ hw_mr; TYPE_2__ ibmr; TYPE_5__ info; int /*<<< orphan*/  type; struct qedr_dev* dev; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_3__* ops; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int (* rdma_alloc_tid ) (int /*<<< orphan*/ ,int*) ;int (* rdma_register_tid ) (int /*<<< orphan*/ ,TYPE_4__*) ;int /*<<< orphan*/  (* rdma_free_tid ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 int ENOMEM ; 
 struct qedr_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDR_MR_FRMR ; 
 int /*<<< orphan*/  QEDR_MSG_MR ; 
 int /*<<< orphan*/  QED_RDMA_TID_FMR ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_pd* get_qedr_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int init_mr_info (struct qedr_dev*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  kfree (struct qedr_mr*) ; 
 struct qedr_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int*) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct qedr_mr *__qedr_alloc_mr(struct ib_pd *ibpd,
				       int max_page_list_len)
{
	struct qedr_pd *pd = get_qedr_pd(ibpd);
	struct qedr_dev *dev = get_qedr_dev(ibpd->device);
	struct qedr_mr *mr;
	int rc = -ENOMEM;

	DP_DEBUG(dev, QEDR_MSG_MR,
		 "qedr_alloc_frmr pd = %d max_page_list_len= %d\n", pd->pd_id,
		 max_page_list_len);

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(rc);

	mr->dev = dev;
	mr->type = QEDR_MR_FRMR;

	rc = init_mr_info(dev, &mr->info, max_page_list_len, 1);
	if (rc)
		goto err0;

	rc = dev->ops->rdma_alloc_tid(dev->rdma_ctx, &mr->hw_mr.itid);
	if (rc) {
		DP_ERR(dev, "roce alloc tid returned an error %d\n", rc);
		goto err0;
	}

	/* Index only, 18 bit long, lkey = itid << 8 | key */
	mr->hw_mr.tid_type = QED_RDMA_TID_FMR;
	mr->hw_mr.key = 0;
	mr->hw_mr.pd = pd->pd_id;
	mr->hw_mr.local_read = 1;
	mr->hw_mr.local_write = 0;
	mr->hw_mr.remote_read = 0;
	mr->hw_mr.remote_write = 0;
	mr->hw_mr.remote_atomic = 0;
	mr->hw_mr.mw_bind = false;
	mr->hw_mr.pbl_ptr = 0;
	mr->hw_mr.pbl_two_level = mr->info.pbl_info.two_layered;
	mr->hw_mr.pbl_page_size_log = ilog2(mr->info.pbl_info.pbl_size);
	mr->hw_mr.fbo = 0;
	mr->hw_mr.length = 0;
	mr->hw_mr.vaddr = 0;
	mr->hw_mr.zbva = false;
	mr->hw_mr.phy_mr = true;
	mr->hw_mr.dma_mr = false;

	rc = dev->ops->rdma_register_tid(dev->rdma_ctx, &mr->hw_mr);
	if (rc) {
		DP_ERR(dev, "roce register tid returned an error %d\n", rc);
		goto err1;
	}

	mr->ibmr.lkey = mr->hw_mr.itid << 8 | mr->hw_mr.key;
	mr->ibmr.rkey = mr->ibmr.lkey;

	DP_DEBUG(dev, QEDR_MSG_MR, "alloc frmr: %x\n", mr->ibmr.lkey);
	return mr;

err1:
	dev->ops->rdma_free_tid(dev->rdma_ctx, mr->hw_mr.itid);
err0:
	kfree(mr);
	return ERR_PTR(rc);
}