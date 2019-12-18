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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct nvme_queue {int /*<<< orphan*/  cq_vector; int /*<<< orphan*/  cq_poll_lock; int /*<<< orphan*/  flags; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMEQ_POLLED ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_complete_cqes (struct nvme_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_process_cq (struct nvme_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_poll_irqdisable(struct nvme_queue *nvmeq, unsigned int tag)
{
	struct pci_dev *pdev = to_pci_dev(nvmeq->dev->dev);
	u16 start, end;
	int found;

	/*
	 * For a poll queue we need to protect against the polling thread
	 * using the CQ lock.  For normal interrupt driven threads we have
	 * to disable the interrupt to avoid racing with it.
	 */
	if (test_bit(NVMEQ_POLLED, &nvmeq->flags)) {
		spin_lock(&nvmeq->cq_poll_lock);
		found = nvme_process_cq(nvmeq, &start, &end, tag);
		spin_unlock(&nvmeq->cq_poll_lock);
	} else {
		disable_irq(pci_irq_vector(pdev, nvmeq->cq_vector));
		found = nvme_process_cq(nvmeq, &start, &end, tag);
		enable_irq(pci_irq_vector(pdev, nvmeq->cq_vector));
	}

	nvme_complete_cqes(nvmeq, start, end);
	return found;
}