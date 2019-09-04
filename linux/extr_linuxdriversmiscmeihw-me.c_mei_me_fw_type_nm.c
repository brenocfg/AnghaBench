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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CFG_HFS_2 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  trace_mei_pci_cfg_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mei_me_fw_type_nm(struct pci_dev *pdev)
{
	u32 reg;

	pci_read_config_dword(pdev, PCI_CFG_HFS_2, &reg);
	trace_mei_pci_cfg_read(&pdev->dev, "PCI_CFG_HFS_2", PCI_CFG_HFS_2, reg);
	/* make sure that bit 9 (NM) is up and bit 10 (DM) is down */
	return (reg & 0x600) == 0x200;
}