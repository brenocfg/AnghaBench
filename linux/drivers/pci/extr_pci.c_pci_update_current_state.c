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
typedef  int u16 ;
struct pci_dev {int current_state; scalar_t__ pm_cap; } ;
typedef  int pci_power_t ;

/* Variables and functions */
 scalar_t__ PCI_D3cold ; 
 scalar_t__ PCI_PM_CTRL ; 
 int PCI_PM_CTRL_STATE_MASK ; 
 int /*<<< orphan*/  pci_device_is_present (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 scalar_t__ platform_pci_get_power_state (struct pci_dev*) ; 

void pci_update_current_state(struct pci_dev *dev, pci_power_t state)
{
	if (platform_pci_get_power_state(dev) == PCI_D3cold ||
	    !pci_device_is_present(dev)) {
		dev->current_state = PCI_D3cold;
	} else if (dev->pm_cap) {
		u16 pmcsr;

		pci_read_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
		dev->current_state = (pmcsr & PCI_PM_CTRL_STATE_MASK);
	} else {
		dev->current_state = state;
	}
}