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
struct pci_dn {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  is_virtfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeh_add_device_early (struct pci_dn*) ; 
 int /*<<< orphan*/  eeh_add_device_late (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_sysfs_add_device (struct pci_dev*) ; 
 struct pci_dn* pci_get_pdn (struct pci_dev*) ; 

void pnv_pcibios_bus_add_device(struct pci_dev *pdev)
{
	struct pci_dn *pdn = pci_get_pdn(pdev);

	if (!pdev->is_virtfn)
		return;

	/*
	 * The following operations will fail if VF's sysfs files
	 * aren't created or its resources aren't finalized.
	 */
	eeh_add_device_early(pdn);
	eeh_add_device_late(pdev);
	eeh_sysfs_add_device(pdev);
}