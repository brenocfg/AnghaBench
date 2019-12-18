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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int BIR_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMWIN_APERTURE ; 
 int MEMWIN_BASE ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_BASE_WIN_A ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WINDOW_V (scalar_t__) ; 
 int /*<<< orphan*/  csio_rd_reg32 (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_t5_set_mem_win(struct csio_hw *hw, uint32_t win)
{
	u32 mem_win_base;
	/*
	 * Truncation intentional: we only read the bottom 32-bits of the
	 * 64-bit BAR0/BAR1 ...  We use the hardware backdoor mechanism to
	 * read BAR0 instead of using pci_resource_start() because we could be
	 * operating from within a Virtual Machine which is trapping our
	 * accesses to our Configuration Space and we need to set up the PCI-E
	 * Memory Window decoders with the actual addresses which will be
	 * coming across the PCI-E link.
	 */

	/* For T5, only relative offset inside the PCIe BAR is passed */
	mem_win_base = MEMWIN_BASE;

	/*
	 * Set up memory window for accessing adapter memory ranges.  (Read
	 * back MA register to ensure that changes propagate before we attempt
	 * to use the new values.)
	 */
	csio_wr_reg32(hw, mem_win_base | BIR_V(0) |
			  WINDOW_V(ilog2(MEMWIN_APERTURE) - 10),
			  PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, win));
	csio_rd_reg32(hw,
		      PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, win));

	return 0;
}