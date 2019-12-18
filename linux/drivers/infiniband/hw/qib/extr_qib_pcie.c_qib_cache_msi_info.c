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
typedef  int u16 ;
struct qib_devdata {int msi_data; int /*<<< orphan*/  msi_hi; int /*<<< orphan*/  msi_lo; struct pci_dev* pcidev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_MSI_ADDRESS_HI ; 
 scalar_t__ PCI_MSI_ADDRESS_LO ; 
 int PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_64BIT ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 

__attribute__((used)) static void qib_cache_msi_info(struct qib_devdata *dd, int pos)
{
	struct pci_dev *pdev = dd->pcidev;
	u16 control;

	pci_read_config_dword(pdev, pos + PCI_MSI_ADDRESS_LO, &dd->msi_lo);
	pci_read_config_dword(pdev, pos + PCI_MSI_ADDRESS_HI, &dd->msi_hi);
	pci_read_config_word(pdev, pos + PCI_MSI_FLAGS, &control);

	/* now save the data (vector) info */
	pci_read_config_word(pdev,
			     pos + ((control & PCI_MSI_FLAGS_64BIT) ? 12 : 8),
			     &dd->msi_data);
}