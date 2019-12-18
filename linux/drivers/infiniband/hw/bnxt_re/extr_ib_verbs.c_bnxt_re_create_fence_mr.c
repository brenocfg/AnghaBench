#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct ib_mw {int dummy; } ;
struct device {int dummy; } ;
struct bnxt_re_fence_data {struct ib_mw* mw; scalar_t__ va; struct bnxt_re_mr* mr; void* dma_addr; } ;
struct bnxt_re_pd {int /*<<< orphan*/  ib_pd; int /*<<< orphan*/  qplib_pd; struct bnxt_re_dev* rdev; struct bnxt_re_fence_data fence; } ;
struct TYPE_9__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  total_size; void* va; int /*<<< orphan*/  lkey; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * pd; } ;
struct TYPE_8__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct bnxt_re_mr {TYPE_4__ qplib_mr; TYPE_3__ ib_mr; struct bnxt_re_dev* rdev; } ;
struct bnxt_re_dev {int /*<<< orphan*/  qplib_res; TYPE_2__* en_dev; } ;
typedef  void* dma_addr_t ;
struct TYPE_7__ {TYPE_1__* pdev; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_RE_FENCE_BYTES ; 
 int /*<<< orphan*/  BNXT_RE_FENCE_PBL_SIZE ; 
 int /*<<< orphan*/  CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int /*<<< orphan*/  IB_MW_TYPE_1 ; 
 scalar_t__ IS_ERR (struct ib_mw*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct ib_mw*) ; 
 int /*<<< orphan*/  __from_ib_access_flags (int) ; 
 int bnxt_qplib_alloc_mrw (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int bnxt_qplib_reg_mr (int /*<<< orphan*/ *,TYPE_4__*,void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ib_mw* bnxt_re_alloc_mw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_create_fence_wqe (struct bnxt_re_pd*) ; 
 int /*<<< orphan*/  bnxt_re_destroy_fence_mr (struct bnxt_re_pd*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 void* dma_map_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,void*) ; 
 struct bnxt_re_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 

__attribute__((used)) static int bnxt_re_create_fence_mr(struct bnxt_re_pd *pd)
{
	int mr_access_flags = IB_ACCESS_LOCAL_WRITE | IB_ACCESS_MW_BIND;
	struct bnxt_re_fence_data *fence = &pd->fence;
	struct bnxt_re_dev *rdev = pd->rdev;
	struct device *dev = &rdev->en_dev->pdev->dev;
	struct bnxt_re_mr *mr = NULL;
	dma_addr_t dma_addr = 0;
	struct ib_mw *mw;
	u64 pbl_tbl;
	int rc;

	dma_addr = dma_map_single(dev, fence->va, BNXT_RE_FENCE_BYTES,
				  DMA_BIDIRECTIONAL);
	rc = dma_mapping_error(dev, dma_addr);
	if (rc) {
		dev_err(rdev_to_dev(rdev), "Failed to dma-map fence-MR-mem\n");
		rc = -EIO;
		fence->dma_addr = 0;
		goto fail;
	}
	fence->dma_addr = dma_addr;

	/* Allocate a MR */
	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr) {
		rc = -ENOMEM;
		goto fail;
	}
	fence->mr = mr;
	mr->rdev = rdev;
	mr->qplib_mr.pd = &pd->qplib_pd;
	mr->qplib_mr.type = CMDQ_ALLOCATE_MRW_MRW_FLAGS_PMR;
	mr->qplib_mr.flags = __from_ib_access_flags(mr_access_flags);
	rc = bnxt_qplib_alloc_mrw(&rdev->qplib_res, &mr->qplib_mr);
	if (rc) {
		dev_err(rdev_to_dev(rdev), "Failed to alloc fence-HW-MR\n");
		goto fail;
	}

	/* Register MR */
	mr->ib_mr.lkey = mr->qplib_mr.lkey;
	mr->qplib_mr.va = (u64)(unsigned long)fence->va;
	mr->qplib_mr.total_size = BNXT_RE_FENCE_BYTES;
	pbl_tbl = dma_addr;
	rc = bnxt_qplib_reg_mr(&rdev->qplib_res, &mr->qplib_mr, &pbl_tbl,
			       BNXT_RE_FENCE_PBL_SIZE, false, PAGE_SIZE);
	if (rc) {
		dev_err(rdev_to_dev(rdev), "Failed to register fence-MR\n");
		goto fail;
	}
	mr->ib_mr.rkey = mr->qplib_mr.rkey;

	/* Create a fence MW only for kernel consumers */
	mw = bnxt_re_alloc_mw(&pd->ib_pd, IB_MW_TYPE_1, NULL);
	if (IS_ERR(mw)) {
		dev_err(rdev_to_dev(rdev),
			"Failed to create fence-MW for PD: %p\n", pd);
		rc = PTR_ERR(mw);
		goto fail;
	}
	fence->mw = mw;

	bnxt_re_create_fence_wqe(pd);
	return 0;

fail:
	bnxt_re_destroy_fence_mr(pd);
	return rc;
}