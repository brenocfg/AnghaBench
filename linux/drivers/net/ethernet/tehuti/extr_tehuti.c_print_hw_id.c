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
typedef  int /*<<< orphan*/  u16 ;
struct pci_nic {int port_num; scalar_t__ regs; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDX_NIC_NAME ; 
 scalar_t__ FPGA_SEED ; 
 scalar_t__ FPGA_VER ; 
 int /*<<< orphan*/  GET_DEV_CTRL_MAXPL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_DEV_CTRL_MRRS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_LINK_STATUS_LANES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DEV_CTRL_REG ; 
 int /*<<< orphan*/  PCI_LINK_STATUS_REG ; 
 scalar_t__ SROM_VER ; 
 struct pci_nic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void print_hw_id(struct pci_dev *pdev)
{
	struct pci_nic *nic = pci_get_drvdata(pdev);
	u16 pci_link_status = 0;
	u16 pci_ctrl = 0;

	pci_read_config_word(pdev, PCI_LINK_STATUS_REG, &pci_link_status);
	pci_read_config_word(pdev, PCI_DEV_CTRL_REG, &pci_ctrl);

	pr_info("%s%s\n", BDX_NIC_NAME,
		nic->port_num == 1 ? "" : ", 2-Port");
	pr_info("srom 0x%x fpga %d build %u lane# %d max_pl 0x%x mrrs 0x%x\n",
		readl(nic->regs + SROM_VER), readl(nic->regs + FPGA_VER) & 0xFFF,
		readl(nic->regs + FPGA_SEED),
		GET_LINK_STATUS_LANES(pci_link_status),
		GET_DEV_CTRL_MAXPL(pci_ctrl), GET_DEV_CTRL_MRRS(pci_ctrl));
}