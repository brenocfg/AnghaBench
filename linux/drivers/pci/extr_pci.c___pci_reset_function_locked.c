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
 int ENOTTY ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pci_af_flr (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_dev_reset_slot_function (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_dev_specific_reset (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_parent_bus_reset (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_pm_reset (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pcie_flr (struct pci_dev*) ; 
 scalar_t__ pcie_has_flr (struct pci_dev*) ; 

int __pci_reset_function_locked(struct pci_dev *dev)
{
	int rc;

	might_sleep();

	/*
	 * A reset method returns -ENOTTY if it doesn't support this device
	 * and we should try the next method.
	 *
	 * If it returns 0 (success), we're finished.  If it returns any
	 * other error, we're also finished: this indicates that further
	 * reset mechanisms might be broken on the device.
	 */
	rc = pci_dev_specific_reset(dev, 0);
	if (rc != -ENOTTY)
		return rc;
	if (pcie_has_flr(dev)) {
		rc = pcie_flr(dev);
		if (rc != -ENOTTY)
			return rc;
	}
	rc = pci_af_flr(dev, 0);
	if (rc != -ENOTTY)
		return rc;
	rc = pci_pm_reset(dev, 0);
	if (rc != -ENOTTY)
		return rc;
	rc = pci_dev_reset_slot_function(dev, 0);
	if (rc != -ENOTTY)
		return rc;
	return pci_parent_bus_reset(dev, 0);
}