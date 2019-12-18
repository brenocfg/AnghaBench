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
struct pcie_pme_service_data {int noirq; int /*<<< orphan*/  lock; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcie_clear_root_pme_status (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_pme_interrupt_enable (struct pci_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcie_pme_disable_interrupt(struct pci_dev *port,
				       struct pcie_pme_service_data *data)
{
	spin_lock_irq(&data->lock);
	pcie_pme_interrupt_enable(port, false);
	pcie_clear_root_pme_status(port);
	data->noirq = true;
	spin_unlock_irq(&data->lock);
}