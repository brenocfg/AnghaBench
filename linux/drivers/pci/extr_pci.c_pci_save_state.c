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
struct pci_dev {int state_saved; int /*<<< orphan*/ * saved_config_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_save_dpc_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_ltr_state (struct pci_dev*) ; 
 int pci_save_pcie_state (struct pci_dev*) ; 
 int pci_save_pcix_state (struct pci_dev*) ; 
 int pci_save_vc_state (struct pci_dev*) ; 

int pci_save_state(struct pci_dev *dev)
{
	int i;
	/* XXX: 100% dword access ok here? */
	for (i = 0; i < 16; i++)
		pci_read_config_dword(dev, i * 4, &dev->saved_config_space[i]);
	dev->state_saved = true;

	i = pci_save_pcie_state(dev);
	if (i != 0)
		return i;

	i = pci_save_pcix_state(dev);
	if (i != 0)
		return i;

	pci_save_ltr_state(dev);
	pci_save_dpc_state(dev);
	return pci_save_vc_state(dev);
}