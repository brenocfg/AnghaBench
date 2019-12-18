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
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

int pci_back_from_sleep(struct pci_dev *dev)
{
	pci_enable_wake(dev, PCI_D0, false);
	return pci_set_power_state(dev, PCI_D0);
}