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
struct pci_dev {int /*<<< orphan*/  current_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CSI_CONTROL ; 
 int /*<<< orphan*/  PCI_CSI_CONTROL_PORTS_OFF_MASK ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  PCI_INTERRUPT_CTRL ; 
 int /*<<< orphan*/  isp_set_power (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int isp_pci_suspend(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	u32 val;

	pci_write_config_dword(pdev, PCI_INTERRUPT_CTRL, 0);

	/*
	 * MRFLD IUNIT DPHY is located in an always-power-on island
	 * MRFLD HW design need all CSI ports are disabled before
	 * powering down the IUNIT.
	 */
	pci_read_config_dword(pdev, PCI_CSI_CONTROL, &val);
	val |= PCI_CSI_CONTROL_PORTS_OFF_MASK;
	pci_write_config_dword(pdev, PCI_CSI_CONTROL, val);

	/*
	 * We lose config space access when punit power gates
	 * the ISP. Can't use pci_set_power_state() because
	 * pmcsr won't actually change when we write to it.
	 */
	pci_save_state(pdev);
	pdev->current_state = PCI_D3cold;
	isp_set_power(pdev, false);

	return 0;
}