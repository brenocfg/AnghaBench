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
struct pqi_ctrl_info {int num_msix_vectors_enabled; int /*<<< orphan*/  irq_mode; TYPE_1__* pci_dev; int /*<<< orphan*/  num_queue_groups; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MODE_MSIX ; 
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  PQI_MIN_MSIX_VECTORS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int pci_alloc_irq_vectors (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pqi_enable_msix_interrupts(struct pqi_ctrl_info *ctrl_info)
{
	int num_vectors_enabled;

	num_vectors_enabled = pci_alloc_irq_vectors(ctrl_info->pci_dev,
			PQI_MIN_MSIX_VECTORS, ctrl_info->num_queue_groups,
			PCI_IRQ_MSIX | PCI_IRQ_AFFINITY);
	if (num_vectors_enabled < 0) {
		dev_err(&ctrl_info->pci_dev->dev,
			"MSI-X init failed with error %d\n",
			num_vectors_enabled);
		return num_vectors_enabled;
	}

	ctrl_info->num_msix_vectors_enabled = num_vectors_enabled;
	ctrl_info->irq_mode = IRQ_MODE_MSIX;
	return 0;
}