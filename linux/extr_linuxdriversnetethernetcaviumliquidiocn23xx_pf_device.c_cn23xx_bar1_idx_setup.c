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
 int /*<<< orphan*/  CN23XX_PEM_BAR1_INDEX_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCI_BAR1_MASK ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cn23xx_bar1_idx_setup(struct octeon_device *oct, u64 core_addr,
				  u32 idx, int valid)
{
	u64 bar1;
	u64 reg_adr;

	if (!valid) {
		reg_adr = lio_pci_readq(
			oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
		WRITE_ONCE(bar1, reg_adr);
		lio_pci_writeq(oct, (READ_ONCE(bar1) & 0xFFFFFFFEULL),
			       CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
		reg_adr = lio_pci_readq(
			oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));
		WRITE_ONCE(bar1, reg_adr);
		return;
	}

	/*  The PEM(0..3)_BAR1_INDEX(0..15)[ADDR_IDX]<23:4> stores
	 *  bits <41:22> of the Core Addr
	 */
	lio_pci_writeq(oct, (((core_addr >> 22) << 4) | PCI_BAR1_MASK),
		       CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx));

	WRITE_ONCE(bar1, lio_pci_readq(
		   oct, CN23XX_PEM_BAR1_INDEX_REG(oct->pcie_port, idx)));
}