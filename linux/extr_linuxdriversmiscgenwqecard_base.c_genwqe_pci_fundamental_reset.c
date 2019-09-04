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
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_cfg_access_lock (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_cfg_access_unlock (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_set_pcie_reset_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_deassert_reset ; 
 int /*<<< orphan*/  pcie_warm_reset ; 

__attribute__((used)) static int genwqe_pci_fundamental_reset(struct pci_dev *pci_dev)
{
	int rc;

	/*
	 * lock pci config space access from userspace,
	 * save state and issue PCIe fundamental reset
	 */
	pci_cfg_access_lock(pci_dev);
	pci_save_state(pci_dev);
	rc = pci_set_pcie_reset_state(pci_dev, pcie_warm_reset);
	if (!rc) {
		/* keep PCIe reset asserted for 250ms */
		msleep(250);
		pci_set_pcie_reset_state(pci_dev, pcie_deassert_reset);
		/* Wait for 2s to reload flash and train the link */
		msleep(2000);
	}
	pci_restore_state(pci_dev);
	pci_cfg_access_unlock(pci_dev);
	return rc;
}