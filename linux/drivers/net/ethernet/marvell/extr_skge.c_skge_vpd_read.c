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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_VPD_ADDR ; 
 int PCI_VPD_ADDR_F ; 
 scalar_t__ PCI_VPD_DATA ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static u32 skge_vpd_read(struct pci_dev *pdev, int cap, u16 offset)
{
	u32 val;

	pci_write_config_word(pdev, cap + PCI_VPD_ADDR, offset);

	do {
		pci_read_config_word(pdev, cap + PCI_VPD_ADDR, &offset);
	} while (!(offset & PCI_VPD_ADDR_F));

	pci_read_config_dword(pdev, cap + PCI_VPD_DATA, &val);
	return val;
}