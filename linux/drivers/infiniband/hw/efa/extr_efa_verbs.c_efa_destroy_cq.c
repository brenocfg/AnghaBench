#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_udata {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct efa_dev {TYPE_1__* pdev; int /*<<< orphan*/  ibdev; } ;
struct efa_cq {int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cq_idx; int /*<<< orphan*/  cpu_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efa_destroy_cq_idx (struct efa_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct efa_cq* to_ecq (struct ib_cq*) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 

void efa_destroy_cq(struct ib_cq *ibcq, struct ib_udata *udata)
{
	struct efa_dev *dev = to_edev(ibcq->device);
	struct efa_cq *cq = to_ecq(ibcq);

	ibdev_dbg(&dev->ibdev,
		  "Destroy cq[%d] virt[0x%p] freed: size[%lu], dma[%pad]\n",
		  cq->cq_idx, cq->cpu_addr, cq->size, &cq->dma_addr);

	efa_destroy_cq_idx(dev, cq->cq_idx);
	dma_unmap_single(&dev->pdev->dev, cq->dma_addr, cq->size,
			 DMA_FROM_DEVICE);
}