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
struct pci_dev {scalar_t__ current_state; int pme_support; int /*<<< orphan*/  pm_cap; } ;
typedef  int pci_power_t ;

/* Variables and functions */
 int PCI_D0 ; 
#define  PCI_D1 131 
#define  PCI_D2 130 
 scalar_t__ PCI_D3cold ; 
 int PCI_D3hot ; 
#define  PCI_POWER_ERROR 129 
#define  PCI_UNKNOWN 128 
 int /*<<< orphan*/  pci_no_d1d2 (struct pci_dev*) ; 
 int platform_pci_choose_state (struct pci_dev*) ; 
 scalar_t__ platform_pci_power_manageable (struct pci_dev*) ; 

__attribute__((used)) static pci_power_t pci_target_state(struct pci_dev *dev, bool wakeup)
{
	pci_power_t target_state = PCI_D3hot;

	if (platform_pci_power_manageable(dev)) {
		/*
		 * Call the platform to find the target state for the device.
		 */
		pci_power_t state = platform_pci_choose_state(dev);

		switch (state) {
		case PCI_POWER_ERROR:
		case PCI_UNKNOWN:
			break;
		case PCI_D1:
		case PCI_D2:
			if (pci_no_d1d2(dev))
				break;
			/* else, fall through */
		default:
			target_state = state;
		}

		return target_state;
	}

	if (!dev->pm_cap)
		target_state = PCI_D0;

	/*
	 * If the device is in D3cold even though it's not power-manageable by
	 * the platform, it may have been powered down by non-standard means.
	 * Best to let it slumber.
	 */
	if (dev->current_state == PCI_D3cold)
		target_state = PCI_D3cold;

	if (wakeup) {
		/*
		 * Find the deepest state from which the device can generate
		 * PME#.
		 */
		if (dev->pme_support) {
			while (target_state
			      && !(dev->pme_support & (1 << target_state)))
				target_state--;
		}
	}

	return target_state;
}