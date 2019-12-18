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
struct igc_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_CTRL ; 
 int IGC_CTRL_DEV_RST ; 
 int /*<<< orphan*/  IGC_ICR ; 
 int /*<<< orphan*/  IGC_IMC ; 
 int /*<<< orphan*/  IGC_RCTL ; 
 int /*<<< orphan*/  IGC_TCTL ; 
 int IGC_TCTL_PSP ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igc_disable_pcie_master (struct igc_hw*) ; 
 scalar_t__ igc_get_auto_rd_done (struct igc_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static s32 igc_reset_hw_base(struct igc_hw *hw)
{
	s32 ret_val;
	u32 ctrl;

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = igc_disable_pcie_master(hw);
	if (ret_val)
		hw_dbg("PCI-E Master disable polling has failed.\n");

	hw_dbg("Masking off all interrupts\n");
	wr32(IGC_IMC, 0xffffffff);

	wr32(IGC_RCTL, 0);
	wr32(IGC_TCTL, IGC_TCTL_PSP);
	wrfl();

	usleep_range(10000, 20000);

	ctrl = rd32(IGC_CTRL);

	hw_dbg("Issuing a global reset to MAC\n");
	wr32(IGC_CTRL, ctrl | IGC_CTRL_DEV_RST);

	ret_val = igc_get_auto_rd_done(hw);
	if (ret_val) {
		/* When auto config read does not complete, do not
		 * return with an error. This can happen in situations
		 * where there is no eeprom and prevents getting link.
		 */
		hw_dbg("Auto Read Done did not complete\n");
	}

	/* Clear any pending interrupt events. */
	wr32(IGC_IMC, 0xffffffff);
	rd32(IGC_ICR);

	return ret_val;
}