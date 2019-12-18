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
struct pci_dev {int /*<<< orphan*/  is_physfn; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  sriov_disable (struct pci_dev*) ; 
 int sriov_enable (struct pci_dev*,int) ; 

int pci_sriov_configure_simple(struct pci_dev *dev, int nr_virtfn)
{
	int rc;

	might_sleep();

	if (!dev->is_physfn)
		return -ENODEV;

	if (pci_vfs_assigned(dev)) {
		pci_warn(dev, "Cannot modify SR-IOV while VFs are assigned\n");
		return -EPERM;
	}

	if (nr_virtfn == 0) {
		sriov_disable(dev);
		return 0;
	}

	rc = sriov_enable(dev, nr_virtfn);
	if (rc < 0)
		return rc;

	return nr_virtfn;
}