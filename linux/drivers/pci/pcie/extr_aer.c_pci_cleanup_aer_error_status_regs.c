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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int aer_cap; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 scalar_t__ PCI_ERR_COR_STATUS ; 
 scalar_t__ PCI_ERR_ROOT_STATUS ; 
 scalar_t__ PCI_ERR_UNCOR_STATUS ; 
 int PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int pci_pcie_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pcie_aer_get_firmware_first (struct pci_dev*) ; 

int pci_cleanup_aer_error_status_regs(struct pci_dev *dev)
{
	int pos;
	u32 status;
	int port_type;

	if (!pci_is_pcie(dev))
		return -ENODEV;

	pos = dev->aer_cap;
	if (!pos)
		return -EIO;

	if (pcie_aer_get_firmware_first(dev))
		return -EIO;

	port_type = pci_pcie_type(dev);
	if (port_type == PCI_EXP_TYPE_ROOT_PORT) {
		pci_read_config_dword(dev, pos + PCI_ERR_ROOT_STATUS, &status);
		pci_write_config_dword(dev, pos + PCI_ERR_ROOT_STATUS, status);
	}

	pci_read_config_dword(dev, pos + PCI_ERR_COR_STATUS, &status);
	pci_write_config_dword(dev, pos + PCI_ERR_COR_STATUS, status);

	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, &status);
	pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, status);

	return 0;
}