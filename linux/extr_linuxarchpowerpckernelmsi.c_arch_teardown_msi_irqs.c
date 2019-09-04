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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown_msi_irqs ) (struct pci_dev*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

void arch_teardown_msi_irqs(struct pci_dev *dev)
{
	struct pci_controller *phb = pci_bus_to_host(dev->bus);

	/*
	 * We can be called even when arch_setup_msi_irqs() returns -ENOSYS,
	 * so check the pointer again.
	 */
	if (phb->controller_ops.teardown_msi_irqs)
		phb->controller_ops.teardown_msi_irqs(dev);
}