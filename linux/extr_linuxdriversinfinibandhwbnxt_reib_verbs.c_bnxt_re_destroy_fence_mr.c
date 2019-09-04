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
struct device {int dummy; } ;
struct bnxt_re_fence_data {scalar_t__ dma_addr; struct bnxt_re_mr* mr; int /*<<< orphan*/ * mw; } ;
struct bnxt_re_pd {struct bnxt_re_dev* rdev; struct bnxt_re_fence_data fence; } ;
struct TYPE_6__ {scalar_t__ lkey; scalar_t__ rkey; } ;
struct bnxt_re_mr {int /*<<< orphan*/  qplib_mr; TYPE_3__ ib_mr; } ;
struct bnxt_re_dev {int /*<<< orphan*/  qplib_res; TYPE_2__* en_dev; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_RE_FENCE_BYTES ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  bnxt_qplib_dereg_mrw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bnxt_qplib_free_mrw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_dealloc_mw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bnxt_re_mr*) ; 

__attribute__((used)) static void bnxt_re_destroy_fence_mr(struct bnxt_re_pd *pd)
{
	struct bnxt_re_fence_data *fence = &pd->fence;
	struct bnxt_re_dev *rdev = pd->rdev;
	struct device *dev = &rdev->en_dev->pdev->dev;
	struct bnxt_re_mr *mr = fence->mr;

	if (fence->mw) {
		bnxt_re_dealloc_mw(fence->mw);
		fence->mw = NULL;
	}
	if (mr) {
		if (mr->ib_mr.rkey)
			bnxt_qplib_dereg_mrw(&rdev->qplib_res, &mr->qplib_mr,
					     true);
		if (mr->ib_mr.lkey)
			bnxt_qplib_free_mrw(&rdev->qplib_res, &mr->qplib_mr);
		kfree(mr);
		fence->mr = NULL;
	}
	if (fence->dma_addr) {
		dma_unmap_single(dev, fence->dma_addr, BNXT_RE_FENCE_BYTES,
				 DMA_BIDIRECTIONAL);
		fence->dma_addr = 0;
	}
}