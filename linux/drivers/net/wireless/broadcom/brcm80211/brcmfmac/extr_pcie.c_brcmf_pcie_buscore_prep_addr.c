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
 int BRCMF_PCIE_BAR0_REG_SIZE ; 
 int /*<<< orphan*/  BRCMF_PCIE_BAR0_WINDOW ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 brcmf_pcie_buscore_prep_addr(const struct pci_dev *pdev, u32 addr)
{
	u32 ret_addr;

	ret_addr = addr & (BRCMF_PCIE_BAR0_REG_SIZE - 1);
	addr &= ~(BRCMF_PCIE_BAR0_REG_SIZE - 1);
	pci_write_config_dword(pdev, BRCMF_PCIE_BAR0_WINDOW, addr);

	return ret_addr;
}