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
struct TYPE_2__ {int flags; } ;
struct ixgbe_hw {int /*<<< orphan*/  hw_addr; TYPE_1__ mac; } ;

/* Variables and functions */
 int IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_GCR_EXT ; 
 scalar_t__ IXGBE_GCR_EXT_BUFFERS_CLEAR ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 scalar_t__ IXGBE_HLREG0_LPBK ; 
 int /*<<< orphan*/  IXGBE_PCI_DEVICE_STATUS ; 
 int IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ixgbe_pcie_timeout_poll (struct ixgbe_hw*) ; 
 int ixgbe_read_pci_cfg_word (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void ixgbe_clear_tx_pending(struct ixgbe_hw *hw)
{
	u32 gcr_ext, hlreg0, i, poll;
	u16 value;

	/*
	 * If double reset is not requested then all transactions should
	 * already be clear and as such there is no work to do
	 */
	if (!(hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED))
		return;

	/*
	 * Set loopback enable to prevent any transmits from being sent
	 * should the link come up.  This assumes that the RXCTRL.RXEN bit
	 * has already been cleared.
	 */
	hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0 | IXGBE_HLREG0_LPBK);

	/* wait for a last completion before clearing buffers */
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(3000, 6000);

	/* Before proceeding, make sure that the PCIe block does not have
	 * transactions pending.
	 */
	poll = ixgbe_pcie_timeout_poll(hw);
	for (i = 0; i < poll; i++) {
		usleep_range(100, 200);
		value = ixgbe_read_pci_cfg_word(hw, IXGBE_PCI_DEVICE_STATUS);
		if (ixgbe_removed(hw->hw_addr))
			break;
		if (!(value & IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING))
			break;
	}

	/* initiate cleaning flow for buffers in the PCIe transaction layer */
	gcr_ext = IXGBE_READ_REG(hw, IXGBE_GCR_EXT);
	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT,
			gcr_ext | IXGBE_GCR_EXT_BUFFERS_CLEAR);

	/* Flush all writes and allow 20usec for all transactions to clear */
	IXGBE_WRITE_FLUSH(hw);
	udelay(20);

	/* restore previous register values */
	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT, gcr_ext);
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
}