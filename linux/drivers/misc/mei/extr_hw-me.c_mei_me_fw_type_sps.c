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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CFG_HFS_1 ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  trace_mei_pci_cfg_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mei_me_fw_type_sps(struct pci_dev *pdev)
{
	u32 reg;
	unsigned int devfn;

	/*
	 * Read ME FW Status register to check for SPS Firmware
	 * The SPS FW is only signaled in pci function 0
	 */
	devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	pci_bus_read_config_dword(pdev->bus, devfn, PCI_CFG_HFS_1, &reg);
	trace_mei_pci_cfg_read(&pdev->dev, "PCI_CFG_HFS_1", PCI_CFG_HFS_1, reg);
	/* if bits [19:16] = 15, running SPS Firmware */
	return (reg & 0xf0000) == 0xf0000;
}