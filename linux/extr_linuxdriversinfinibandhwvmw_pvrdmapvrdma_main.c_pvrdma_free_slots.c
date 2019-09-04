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
struct pvrdma_dev {TYPE_1__* dsr; scalar_t__ cmd_slot; scalar_t__ resp_slot; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_slot_dma; int /*<<< orphan*/  resp_slot_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvrdma_free_slots(struct pvrdma_dev *dev)
{
	struct pci_dev *pdev = dev->pdev;

	if (dev->resp_slot)
		dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->resp_slot,
				  dev->dsr->resp_slot_dma);
	if (dev->cmd_slot)
		dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->cmd_slot,
				  dev->dsr->cmd_slot_dma);
}