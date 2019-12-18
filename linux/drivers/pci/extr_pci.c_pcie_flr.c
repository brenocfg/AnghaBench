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
struct pci_dev {scalar_t__ imm_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_RESET_READY_POLL_MS ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_BCR_FLR ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pci_dev_wait (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_wait_for_pending_transaction (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcie_flr(struct pci_dev *dev)
{
	if (!pci_wait_for_pending_transaction(dev))
		pci_err(dev, "timed out waiting for pending transaction; performing function level reset anyway\n");

	pcie_capability_set_word(dev, PCI_EXP_DEVCTL, PCI_EXP_DEVCTL_BCR_FLR);

	if (dev->imm_ready)
		return 0;

	/*
	 * Per PCIe r4.0, sec 6.6.2, a device must complete an FLR within
	 * 100ms, but may silently discard requests while the FLR is in
	 * progress.  Wait 100ms before trying to access the device.
	 */
	msleep(100);

	return pci_dev_wait(dev, "FLR", PCIE_RESET_READY_POLL_MS);
}