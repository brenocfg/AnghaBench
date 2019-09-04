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

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int pci_prepare_to_sleep (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int) ; 

__attribute__((used)) static int __e100_power_off(struct pci_dev *pdev, bool wake)
{
	if (wake)
		return pci_prepare_to_sleep(pdev);

	pci_wake_from_d3(pdev, false);
	pci_set_power_state(pdev, PCI_D3hot);

	return 0;
}