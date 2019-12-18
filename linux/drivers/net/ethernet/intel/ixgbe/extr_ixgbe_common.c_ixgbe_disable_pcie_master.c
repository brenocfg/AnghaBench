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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  flags; } ;
struct ixgbe_hw {int /*<<< orphan*/  hw_addr; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int IXGBE_CTRL_GIO_DIS ; 
 int /*<<< orphan*/  IXGBE_ERR_MASTER_REQUESTS_PENDING ; 
 int /*<<< orphan*/  IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_PCI_DEVICE_STATUS ; 
 int IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING ; 
 scalar_t__ IXGBE_PCI_MASTER_DISABLE_TIMEOUT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_STATUS ; 
 int IXGBE_STATUS_GIO ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 scalar_t__ ixgbe_pcie_timeout_poll (struct ixgbe_hw*) ; 
 int ixgbe_read_pci_cfg_word (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 ixgbe_disable_pcie_master(struct ixgbe_hw *hw)
{
	u32 i, poll;
	u16 value;

	/* Always set this bit to ensure any future transactions are blocked */
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, IXGBE_CTRL_GIO_DIS);

	/* Poll for bit to read as set */
	for (i = 0; i < IXGBE_PCI_MASTER_DISABLE_TIMEOUT; i++) {
		if (IXGBE_READ_REG(hw, IXGBE_CTRL) & IXGBE_CTRL_GIO_DIS)
			break;
		usleep_range(100, 120);
	}
	if (i >= IXGBE_PCI_MASTER_DISABLE_TIMEOUT) {
		hw_dbg(hw, "GIO disable did not set - requesting resets\n");
		goto gio_disable_fail;
	}

	/* Exit if master requests are blocked */
	if (!(IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO) ||
	    ixgbe_removed(hw->hw_addr))
		return 0;

	/* Poll for master request bit to clear */
	for (i = 0; i < IXGBE_PCI_MASTER_DISABLE_TIMEOUT; i++) {
		udelay(100);
		if (!(IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO))
			return 0;
	}

	/*
	 * Two consecutive resets are required via CTRL.RST per datasheet
	 * 5.2.5.3.2 Master Disable.  We set a flag to inform the reset routine
	 * of this need.  The first reset prevents new master requests from
	 * being issued by our device.  We then must wait 1usec or more for any
	 * remaining completions from the PCIe bus to trickle in, and then reset
	 * again to clear out any effects they may have had on our device.
	 */
	hw_dbg(hw, "GIO Master Disable bit didn't clear - requesting resets\n");
gio_disable_fail:
	hw->mac.flags |= IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;

	if (hw->mac.type >= ixgbe_mac_X550)
		return 0;

	/*
	 * Before proceeding, make sure that the PCIe block does not have
	 * transactions pending.
	 */
	poll = ixgbe_pcie_timeout_poll(hw);
	for (i = 0; i < poll; i++) {
		udelay(100);
		value = ixgbe_read_pci_cfg_word(hw, IXGBE_PCI_DEVICE_STATUS);
		if (ixgbe_removed(hw->hw_addr))
			return 0;
		if (!(value & IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING))
			return 0;
	}

	hw_dbg(hw, "PCIe transaction pending bit also did not clear.\n");
	return IXGBE_ERR_MASTER_REQUESTS_PENDING;
}