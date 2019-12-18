#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int dummy; } ;
struct nvme_queue {int /*<<< orphan*/  sq_cmds; int /*<<< orphan*/  sq_dma_addr; int /*<<< orphan*/  flags; } ;
struct nvme_dev {int cmbsz; int /*<<< orphan*/  dev; scalar_t__ cmb_use_sqes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVMEQ_SQ_CMB ; 
 int NVME_CMBSZ_SQS ; 
 int /*<<< orphan*/  SQ_SIZE (struct nvme_queue*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_alloc_p2pmem (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_p2pmem (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_p2pmem_virt_to_bus (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_alloc_sq_cmds(struct nvme_dev *dev, struct nvme_queue *nvmeq,
				int qid)
{
	struct pci_dev *pdev = to_pci_dev(dev->dev);

	if (qid && dev->cmb_use_sqes && (dev->cmbsz & NVME_CMBSZ_SQS)) {
		nvmeq->sq_cmds = pci_alloc_p2pmem(pdev, SQ_SIZE(nvmeq));
		if (nvmeq->sq_cmds) {
			nvmeq->sq_dma_addr = pci_p2pmem_virt_to_bus(pdev,
							nvmeq->sq_cmds);
			if (nvmeq->sq_dma_addr) {
				set_bit(NVMEQ_SQ_CMB, &nvmeq->flags);
				return 0;
			}

			pci_free_p2pmem(pdev, nvmeq->sq_cmds, SQ_SIZE(nvmeq));
		}
	}

	nvmeq->sq_cmds = dma_alloc_coherent(dev->dev, SQ_SIZE(nvmeq),
				&nvmeq->sq_dma_addr, GFP_KERNEL);
	if (!nvmeq->sq_cmds)
		return -ENOMEM;
	return 0;
}