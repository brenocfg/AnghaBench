#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {scalar_t__ t4_bar0; TYPE_1__ params; } ;

/* Variables and functions */
 int EDRAM0_SIZE_G (int) ; 
 int ENXIO ; 
 int EXT_MEM0_SIZE_G (int) ; 
 int /*<<< orphan*/  MA_EDRAM0_BAR_A ; 
 int /*<<< orphan*/  MA_EXT_MEMORY0_BAR_A ; 
 int MEM_HMA ; 
 int MEM_MC0 ; 
 int MEM_MC1 ; 
 int PCIEOFST_G (int) ; 
 int PCIEOFST_SHIFT_X ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_BASE_WIN_A ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 int WINDOW_G (int) ; 
 int WINDOW_SHIFT_X ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int t4_memory_rw_init(struct adapter *adap, int win, int mtype, u32 *mem_off,
		      u32 *mem_base, u32 *mem_aperture)
{
	u32 edc_size, mc_size, mem_reg;

	/* Offset into the region of memory which is being accessed
	 * MEM_EDC0 = 0
	 * MEM_EDC1 = 1
	 * MEM_MC   = 2 -- MEM_MC for chips with only 1 memory controller
	 * MEM_MC1  = 3 -- for chips with 2 memory controllers (e.g. T5)
	 * MEM_HMA  = 4
	 */
	edc_size  = EDRAM0_SIZE_G(t4_read_reg(adap, MA_EDRAM0_BAR_A));
	if (mtype == MEM_HMA) {
		*mem_off = 2 * (edc_size * 1024 * 1024);
	} else if (mtype != MEM_MC1) {
		*mem_off = (mtype * (edc_size * 1024 * 1024));
	} else {
		mc_size = EXT_MEM0_SIZE_G(t4_read_reg(adap,
						      MA_EXT_MEMORY0_BAR_A));
		*mem_off = (MEM_MC0 * edc_size + mc_size) * 1024 * 1024;
	}

	/* Each PCI-E Memory Window is programmed with a window size -- or
	 * "aperture" -- which controls the granularity of its mapping onto
	 * adapter memory.  We need to grab that aperture in order to know
	 * how to use the specified window.  The window is also programmed
	 * with the base address of the Memory Window in BAR0's address
	 * space.  For T4 this is an absolute PCI-E Bus Address.  For T5
	 * the address is relative to BAR0.
	 */
	mem_reg = t4_read_reg(adap,
			      PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A,
						  win));
	/* a dead adapter will return 0xffffffff for PIO reads */
	if (mem_reg == 0xffffffff)
		return -ENXIO;

	*mem_aperture = 1 << (WINDOW_G(mem_reg) + WINDOW_SHIFT_X);
	*mem_base = PCIEOFST_G(mem_reg) << PCIEOFST_SHIFT_X;
	if (is_t4(adap->params.chip))
		*mem_base -= adap->t4_bar0;

	return 0;
}