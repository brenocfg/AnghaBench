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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct cxl {int psl_rev; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 int PCI_ERR_UNC_INTN ; 
 int PCI_ERR_UNC_MALF_TLP ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static void cxl_fixup_malformed_tlp(struct cxl *adapter, struct pci_dev *dev)
{
	int aer;
	u32 data;

	if (adapter->psl_rev & 0xf000)
		return;
	if (!(aer = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR)))
		return;
	pci_read_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, &data);
	if (data & PCI_ERR_UNC_MALF_TLP)
		if (data & PCI_ERR_UNC_INTN)
			return;
	data |= PCI_ERR_UNC_MALF_TLP;
	data |= PCI_ERR_UNC_INTN;
	pci_write_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, data);
}