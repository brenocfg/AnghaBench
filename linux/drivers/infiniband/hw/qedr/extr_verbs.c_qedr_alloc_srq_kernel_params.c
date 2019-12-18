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
typedef  int u32 ;
struct rdma_srq_producers {int dummy; } ;
struct qedr_srq_hwq_info {int num_elems; int /*<<< orphan*/  pbl; void* virt_prod_pair_addr; int /*<<< orphan*/  phy_prod_pair_addr; } ;
struct qedr_srq {struct qedr_srq_hwq_info hw_srq; } ;
struct qedr_dev {TYPE_4__* pdev; int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct TYPE_5__ {int max_wr; } ;
struct ib_srq_init_attr {TYPE_1__ attr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_2__* common; } ;
struct TYPE_6__ {int (* chain_alloc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDR_SRQ_WQE_ELEM_SIZE ; 
 int /*<<< orphan*/  QED_CHAIN_CNT_TYPE_U32 ; 
 int /*<<< orphan*/  QED_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  QED_CHAIN_USE_TO_CONSUME_PRODUCE ; 
 int RDMA_MAX_SRQ_WQE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedr_alloc_srq_kernel_params(struct qedr_srq *srq,
					struct qedr_dev *dev,
					struct ib_srq_init_attr *init_attr)
{
	struct qedr_srq_hwq_info *hw_srq = &srq->hw_srq;
	dma_addr_t phy_prod_pair_addr;
	u32 num_elems;
	void *va;
	int rc;

	va = dma_alloc_coherent(&dev->pdev->dev,
				sizeof(struct rdma_srq_producers),
				&phy_prod_pair_addr, GFP_KERNEL);
	if (!va) {
		DP_ERR(dev,
		       "create srq: failed to allocate dma memory for producer\n");
		return -ENOMEM;
	}

	hw_srq->phy_prod_pair_addr = phy_prod_pair_addr;
	hw_srq->virt_prod_pair_addr = va;

	num_elems = init_attr->attr.max_wr * RDMA_MAX_SRQ_WQE_SIZE;
	rc = dev->ops->common->chain_alloc(dev->cdev,
					   QED_CHAIN_USE_TO_CONSUME_PRODUCE,
					   QED_CHAIN_MODE_PBL,
					   QED_CHAIN_CNT_TYPE_U32,
					   num_elems,
					   QEDR_SRQ_WQE_ELEM_SIZE,
					   &hw_srq->pbl, NULL);
	if (rc)
		goto err0;

	hw_srq->num_elems = num_elems;

	return 0;

err0:
	dma_free_coherent(&dev->pdev->dev, sizeof(struct rdma_srq_producers),
			  va, phy_prod_pair_addr);
	return rc;
}