#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_wwn_prefix ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clear_vmdq ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_san_mac_addr ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_rx_addrs ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* get_mac_addr ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int) ;scalar_t__ (* stop_adapter ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  wwpn_prefix; int /*<<< orphan*/  wwnn_prefix; TYPE_2__ ops; scalar_t__ num_rar_entries; scalar_t__ san_mac_rar_index; int /*<<< orphan*/  san_addr; int /*<<< orphan*/  perm_addr; } ;
struct TYPE_4__ {int phy_semaphore_mask; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CLEAR_VMDQ_ALL ; 
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int IXGBE_CTRL_RST ; 
 int IXGBE_CTRL_RST_MASK ; 
 scalar_t__ IXGBE_ERR_RESET_FAILED ; 
 scalar_t__ IXGBE_ERR_SWFW_SYNC ; 
 int IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_RAH_AV ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXPBSIZE (int /*<<< orphan*/ ) ; 
 int IXGBE_RXPBSIZE_SHIFT ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IXGBE_X540_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,...) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_clear_tx_pending (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 ixgbe_reset_hw_X540(struct ixgbe_hw *hw)
{
	s32 status;
	u32 ctrl, i;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;

	/* Call adapter stop to disable tx/rx and clear interrupts */
	status = hw->mac.ops.stop_adapter(hw);
	if (status)
		return status;

	/* flush pending Tx transactions */
	ixgbe_clear_tx_pending(hw);

mac_reset_top:
	status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
	if (status) {
		hw_dbg(hw, "semaphore failed with %d", status);
		return IXGBE_ERR_SWFW_SYNC;
	}

	ctrl = IXGBE_CTRL_RST;
	ctrl |= IXGBE_READ_REG(hw, IXGBE_CTRL);
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	usleep_range(1000, 1200);

	/* Poll for reset bit to self-clear indicating reset is complete */
	for (i = 0; i < 10; i++) {
		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		if (!(ctrl & IXGBE_CTRL_RST_MASK))
			break;
		udelay(1);
	}

	if (ctrl & IXGBE_CTRL_RST_MASK) {
		status = IXGBE_ERR_RESET_FAILED;
		hw_dbg(hw, "Reset polling failed to complete.\n");
	}
	msleep(100);

	/*
	 * Double resets are required for recovery from certain error
	 * conditions.  Between resets, it is necessary to stall to allow time
	 * for any pending HW events to complete.
	 */
	if (hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED) {
		hw->mac.flags &= ~IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;
		goto mac_reset_top;
	}

	/* Set the Rx packet buffer size. */
	IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(0), 384 << IXGBE_RXPBSIZE_SHIFT);

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/*
	 * Store MAC address from RAR0, clear receive address registers, and
	 * clear the multicast table.  Also reset num_rar_entries to 128,
	 * since we modify this value when programming the SAN MAC address.
	 */
	hw->mac.num_rar_entries = IXGBE_X540_MAX_TX_QUEUES;
	hw->mac.ops.init_rx_addrs(hw);

	/* Store the permanent SAN mac address */
	hw->mac.ops.get_san_mac_addr(hw, hw->mac.san_addr);

	/* Add the SAN MAC address to the RAR only if it's a valid address */
	if (is_valid_ether_addr(hw->mac.san_addr)) {
		/* Save the SAN MAC RAR index */
		hw->mac.san_mac_rar_index = hw->mac.num_rar_entries - 1;

		hw->mac.ops.set_rar(hw, hw->mac.san_mac_rar_index,
				    hw->mac.san_addr, 0, IXGBE_RAH_AV);

		/* clear VMDq pool/queue selection for this RAR */
		hw->mac.ops.clear_vmdq(hw, hw->mac.san_mac_rar_index,
				       IXGBE_CLEAR_VMDQ_ALL);

		/* Reserve the last RAR for the SAN MAC address */
		hw->mac.num_rar_entries--;
	}

	/* Store the alternative WWNN/WWPN prefix */
	hw->mac.ops.get_wwn_prefix(hw, &hw->mac.wwnn_prefix,
				   &hw->mac.wwpn_prefix);

	return status;
}