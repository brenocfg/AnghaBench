#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {unsigned int class; int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int DL_FLAG_PM_RUNTIME ; 
 int DL_FLAG_STATELESS ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ device_link_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_create_device_link(struct pci_dev *pdev, unsigned int consumer,
				   unsigned int supplier, unsigned int class,
				   unsigned int class_shift)
{
	struct pci_dev *supplier_pdev;

	if (PCI_FUNC(pdev->devfn) != consumer)
		return;

	supplier_pdev = pci_get_domain_bus_and_slot(pci_domain_nr(pdev->bus),
				pdev->bus->number,
				PCI_DEVFN(PCI_SLOT(pdev->devfn), supplier));
	if (!supplier_pdev || (supplier_pdev->class >> class_shift) != class) {
		pci_dev_put(supplier_pdev);
		return;
	}

	if (device_link_add(&pdev->dev, &supplier_pdev->dev,
			    DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME))
		pci_info(pdev, "D0 power state depends on %s\n",
			 pci_name(supplier_pdev));
	else
		pci_err(pdev, "Cannot enforce power dependency on %s\n",
			pci_name(supplier_pdev));

	pm_runtime_allow(&pdev->dev);
	pci_dev_put(supplier_pdev);
}