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
struct nvme_queue {void* sq_cmds; int /*<<< orphan*/  sq_dma_addr; TYPE_1__* dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  cq_dma_addr; scalar_t__ cqes; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (struct nvme_queue*) ; 
 int /*<<< orphan*/  NVMEQ_SQ_CMB ; 
 int /*<<< orphan*/  SQ_SIZE (struct nvme_queue*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_p2pmem (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_free_queue(struct nvme_queue *nvmeq)
{
	dma_free_coherent(nvmeq->dev->dev, CQ_SIZE(nvmeq),
				(void *)nvmeq->cqes, nvmeq->cq_dma_addr);
	if (!nvmeq->sq_cmds)
		return;

	if (test_and_clear_bit(NVMEQ_SQ_CMB, &nvmeq->flags)) {
		pci_free_p2pmem(to_pci_dev(nvmeq->dev->dev),
				nvmeq->sq_cmds, SQ_SIZE(nvmeq));
	} else {
		dma_free_coherent(nvmeq->dev->dev, SQ_SIZE(nvmeq),
				nvmeq->sq_cmds, nvmeq->sq_dma_addr);
	}
}