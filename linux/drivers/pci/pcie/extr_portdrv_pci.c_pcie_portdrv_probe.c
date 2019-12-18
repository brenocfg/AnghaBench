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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DPM_FLAG_NEVER_SKIP ; 
 int DPM_FLAG_SMART_SUSPEND ; 
 int ENODEV ; 
 scalar_t__ PCI_EXP_TYPE_DOWNSTREAM ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ PCI_EXP_TYPE_UPSTREAM ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pci_bridge_d3_possible (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pcie_port_device_register (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcie_portdrv_probe(struct pci_dev *dev,
					const struct pci_device_id *id)
{
	int status;

	if (!pci_is_pcie(dev) ||
	    ((pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT) &&
	     (pci_pcie_type(dev) != PCI_EXP_TYPE_UPSTREAM) &&
	     (pci_pcie_type(dev) != PCI_EXP_TYPE_DOWNSTREAM)))
		return -ENODEV;

	status = pcie_port_device_register(dev);
	if (status)
		return status;

	pci_save_state(dev);

	dev_pm_set_driver_flags(&dev->dev, DPM_FLAG_NEVER_SKIP |
					   DPM_FLAG_SMART_SUSPEND);

	if (pci_bridge_d3_possible(dev)) {
		/*
		 * Keep the port resumed 100ms to make sure things like
		 * config space accesses from userspace (lspci) will not
		 * cause the port to repeatedly suspend and resume.
		 */
		pm_runtime_set_autosuspend_delay(&dev->dev, 100);
		pm_runtime_use_autosuspend(&dev->dev);
		pm_runtime_mark_last_busy(&dev->dev);
		pm_runtime_put_autosuspend(&dev->dev);
		pm_runtime_allow(&dev->dev);
	}

	return 0;
}