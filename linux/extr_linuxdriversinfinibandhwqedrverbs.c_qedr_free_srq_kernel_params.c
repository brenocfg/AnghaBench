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
struct rdma_srq_producers {int dummy; } ;
struct qedr_srq_hwq_info {int /*<<< orphan*/  phy_prod_pair_addr; int /*<<< orphan*/  virt_prod_pair_addr; int /*<<< orphan*/  pbl; } ;
struct qedr_srq {struct qedr_dev* dev; struct qedr_srq_hwq_info hw_srq; } ;
struct qedr_dev {TYPE_1__* pdev; int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct TYPE_6__ {TYPE_2__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedr_free_srq_kernel_params(struct qedr_srq *srq)
{
	struct qedr_srq_hwq_info *hw_srq = &srq->hw_srq;
	struct qedr_dev *dev = srq->dev;

	dev->ops->common->chain_free(dev->cdev, &hw_srq->pbl);

	dma_free_coherent(&dev->pdev->dev, sizeof(struct rdma_srq_producers),
			  hw_srq->virt_prod_pair_addr,
			  hw_srq->phy_prod_pair_addr);
}