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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_assign_added (struct pci_dev*,int) ; 
 scalar_t__ pci_dev_is_added (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pme_active (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_proc_detach_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_remove_sysfs_dev_files (struct pci_dev*) ; 

__attribute__((used)) static void pci_stop_dev(struct pci_dev *dev)
{
	pci_pme_active(dev, false);

	if (pci_dev_is_added(dev)) {
		device_release_driver(&dev->dev);
		pci_proc_detach_device(dev);
		pci_remove_sysfs_dev_files(dev);

		pci_dev_assign_added(dev, false);
	}
}