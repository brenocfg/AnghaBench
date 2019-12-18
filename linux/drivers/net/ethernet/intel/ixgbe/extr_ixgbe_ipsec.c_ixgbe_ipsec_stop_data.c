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
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int link_up; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int IXGBE_HLREG0_LPBK ; 
 int /*<<< orphan*/  IXGBE_MACC ; 
 int IXGBE_MACC_FLU ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SECRXCTRL ; 
 int IXGBE_SECRXCTRL_RX_DIS ; 
 int /*<<< orphan*/  IXGBE_SECRXSTAT ; 
 int IXGBE_SECRXSTAT_SECRX_RDY ; 
 int /*<<< orphan*/  IXGBE_SECTXCTRL ; 
 int IXGBE_SECTXCTRL_TX_DIS ; 
 int /*<<< orphan*/  IXGBE_SECTXSTAT ; 
 int IXGBE_SECTXSTAT_SECTX_RDY ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void ixgbe_ipsec_stop_data(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	bool link = adapter->link_up;
	u32 t_rdy, r_rdy;
	u32 limit;
	u32 reg;

	/* halt data paths */
	reg = IXGBE_READ_REG(hw, IXGBE_SECTXCTRL);
	reg |= IXGBE_SECTXCTRL_TX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECTXCTRL, reg);

	reg = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	reg |= IXGBE_SECRXCTRL_RX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, reg);

	/* If both Tx and Rx are ready there are no packets
	 * that we need to flush so the loopback configuration
	 * below is not necessary.
	 */
	t_rdy = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT) &
		IXGBE_SECTXSTAT_SECTX_RDY;
	r_rdy = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT) &
		IXGBE_SECRXSTAT_SECRX_RDY;
	if (t_rdy && r_rdy)
		return;

	/* If the tx fifo doesn't have link, but still has data,
	 * we can't clear the tx sec block.  Set the MAC loopback
	 * before block clear
	 */
	if (!link) {
		reg = IXGBE_READ_REG(hw, IXGBE_MACC);
		reg |= IXGBE_MACC_FLU;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, reg);

		reg = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		reg |= IXGBE_HLREG0_LPBK;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, reg);

		IXGBE_WRITE_FLUSH(hw);
		mdelay(3);
	}

	/* wait for the paths to empty */
	limit = 20;
	do {
		mdelay(10);
		t_rdy = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT) &
			IXGBE_SECTXSTAT_SECTX_RDY;
		r_rdy = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT) &
			IXGBE_SECRXSTAT_SECRX_RDY;
	} while (!(t_rdy && r_rdy) && limit--);

	/* undo loopback if we played with it earlier */
	if (!link) {
		reg = IXGBE_READ_REG(hw, IXGBE_MACC);
		reg &= ~IXGBE_MACC_FLU;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, reg);

		reg = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		reg &= ~IXGBE_HLREG0_LPBK;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, reg);

		IXGBE_WRITE_FLUSH(hw);
	}
}