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

/* Variables and functions */
 scalar_t__ PCIBIOS_SUCCESSFUL ; 
 int PCI_CFG_SPACE_EXP_SIZE ; 
 int PCI_CFG_SPACE_SIZE ; 
 scalar_t__ pci_ext_cfg_is_aliased (struct pci_dev*) ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int,int*) ; 

__attribute__((used)) static int pci_cfg_space_size_ext(struct pci_dev *dev)
{
	u32 status;
	int pos = PCI_CFG_SPACE_SIZE;

	if (pci_read_config_dword(dev, pos, &status) != PCIBIOS_SUCCESSFUL)
		return PCI_CFG_SPACE_SIZE;
	if (status == 0xffffffff || pci_ext_cfg_is_aliased(dev))
		return PCI_CFG_SPACE_SIZE;

	return PCI_CFG_SPACE_EXP_SIZE;
}