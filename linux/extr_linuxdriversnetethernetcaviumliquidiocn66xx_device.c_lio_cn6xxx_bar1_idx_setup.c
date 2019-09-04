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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct octeon_device {int /*<<< orphan*/  pcie_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_BAR1_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCI_BAR1_MASK ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 

void
lio_cn6xxx_bar1_idx_setup(struct octeon_device *oct,
			  u64 core_addr,
			  u32 idx,
			  int valid)
{
	u64 bar1;

	if (valid == 0) {
		bar1 = lio_pci_readq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
		lio_pci_writeq(oct, (bar1 & 0xFFFFFFFEULL),
			       CN6XXX_BAR1_REG(idx, oct->pcie_port));
		bar1 = lio_pci_readq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
		return;
	}

	/* Bits 17:4 of the PCI_BAR1_INDEXx stores bits 35:22 of
	 * the Core Addr
	 */
	lio_pci_writeq(oct, (((core_addr >> 22) << 4) | PCI_BAR1_MASK),
		       CN6XXX_BAR1_REG(idx, oct->pcie_port));

	bar1 = lio_pci_readq(oct, CN6XXX_BAR1_REG(idx, oct->pcie_port));
}