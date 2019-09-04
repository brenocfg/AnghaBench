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
struct hfi1_devdata {int /*<<< orphan*/  pci_tph2; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  pci_msix0; int /*<<< orphan*/  pcie_devctl2; int /*<<< orphan*/  pcie_lnkctl; int /*<<< orphan*/  pcie_devctl; int /*<<< orphan*/  pci_command; int /*<<< orphan*/  pci_rom; int /*<<< orphan*/  pcibar1; int /*<<< orphan*/  pcibar0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CFG_TPH2 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_CFG_MSIX0 ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_TPH ; 
 int /*<<< orphan*/  PCI_ROM_ADDRESS ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 scalar_t__ pci_find_ext_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int save_pci_variables(struct hfi1_devdata *dd)
{
	int ret = 0;

	ret = pci_read_config_dword(dd->pcidev, PCI_BASE_ADDRESS_0,
				    &dd->pcibar0);
	if (ret)
		goto error;

	ret = pci_read_config_dword(dd->pcidev, PCI_BASE_ADDRESS_1,
				    &dd->pcibar1);
	if (ret)
		goto error;

	ret = pci_read_config_dword(dd->pcidev, PCI_ROM_ADDRESS, &dd->pci_rom);
	if (ret)
		goto error;

	ret = pci_read_config_word(dd->pcidev, PCI_COMMAND, &dd->pci_command);
	if (ret)
		goto error;

	ret = pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCTL,
					&dd->pcie_devctl);
	if (ret)
		goto error;

	ret = pcie_capability_read_word(dd->pcidev, PCI_EXP_LNKCTL,
					&dd->pcie_lnkctl);
	if (ret)
		goto error;

	ret = pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCTL2,
					&dd->pcie_devctl2);
	if (ret)
		goto error;

	ret = pci_read_config_dword(dd->pcidev, PCI_CFG_MSIX0, &dd->pci_msix0);
	if (ret)
		goto error;

	if (pci_find_ext_capability(dd->pcidev, PCI_EXT_CAP_ID_TPH)) {
		ret = pci_read_config_dword(dd->pcidev, PCIE_CFG_TPH2,
					    &dd->pci_tph2);
		if (ret)
			goto error;
	}
	return 0;

error:
	dd_dev_err(dd, "Unable to read from PCI config\n");
	return ret;
}