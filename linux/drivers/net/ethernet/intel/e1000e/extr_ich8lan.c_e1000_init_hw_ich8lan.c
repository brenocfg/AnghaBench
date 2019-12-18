#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ (* setup_link ) (struct e1000_hw*) ;scalar_t__ (* id_led_init ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {scalar_t__ type; TYPE_2__ ops; int /*<<< orphan*/  mta_reg_count; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ phy; struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_PORT_GEN_CFG ; 
 int /*<<< orphan*/  BM_WUC_HOST_WU_BIT ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_RO_DIS ; 
 int /*<<< orphan*/  E1000_MTA ; 
 int E1000_TXDCTL_FULL_TX_DESC_WB ; 
 int E1000_TXDCTL_MAX_TX_DESC_PREFETCH ; 
 int E1000_TXDCTL_PTHRESH ; 
 int E1000_TXDCTL_WTHRESH ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCIE_ICH8_SNOOP_ALL ; 
 scalar_t__ PCIE_NO_SNOOP_ALL ; 
 int /*<<< orphan*/  TXDCTL (int) ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_ich8lan ; 
 int /*<<< orphan*/  e1000_initialize_hw_bits_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1000_phy_hw_reset_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_init_rx_addrs (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_set_pcie_no_snoop (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_hw_ich8lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 ctrl_ext, txdctl, snoop;
	s32 ret_val;
	u16 i;

	e1000_initialize_hw_bits_ich8lan(hw);

	/* Initialize identification LED */
	ret_val = mac->ops.id_led_init(hw);
	/* An error is not fatal and we should not stop init due to this */
	if (ret_val)
		e_dbg("Error initializing identification LED\n");

	/* Setup the receive address. */
	e1000e_init_rx_addrs(hw, mac->rar_entry_count);

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	for (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);

	/* The 82578 Rx buffer will stall if wakeup is enabled in host and
	 * the ME.  Disable wakeup by clearing the host wakeup bit.
	 * Reset the phy after disabling host wakeup to reset the Rx buffer.
	 */
	if (hw->phy.type == e1000_phy_82578) {
		e1e_rphy(hw, BM_PORT_GEN_CFG, &i);
		i &= ~BM_WUC_HOST_WU_BIT;
		e1e_wphy(hw, BM_PORT_GEN_CFG, i);
		ret_val = e1000_phy_hw_reset_ich8lan(hw);
		if (ret_val)
			return ret_val;
	}

	/* Setup link and flow control */
	ret_val = mac->ops.setup_link(hw);

	/* Set the transmit descriptor write-back policy for both queues */
	txdctl = er32(TXDCTL(0));
	txdctl = ((txdctl & ~E1000_TXDCTL_WTHRESH) |
		  E1000_TXDCTL_FULL_TX_DESC_WB);
	txdctl = ((txdctl & ~E1000_TXDCTL_PTHRESH) |
		  E1000_TXDCTL_MAX_TX_DESC_PREFETCH);
	ew32(TXDCTL(0), txdctl);
	txdctl = er32(TXDCTL(1));
	txdctl = ((txdctl & ~E1000_TXDCTL_WTHRESH) |
		  E1000_TXDCTL_FULL_TX_DESC_WB);
	txdctl = ((txdctl & ~E1000_TXDCTL_PTHRESH) |
		  E1000_TXDCTL_MAX_TX_DESC_PREFETCH);
	ew32(TXDCTL(1), txdctl);

	/* ICH8 has opposite polarity of no_snoop bits.
	 * By default, we should use snoop behavior.
	 */
	if (mac->type == e1000_ich8lan)
		snoop = PCIE_ICH8_SNOOP_ALL;
	else
		snoop = (u32)~(PCIE_NO_SNOOP_ALL);
	e1000e_set_pcie_no_snoop(hw, snoop);

	ctrl_ext = er32(CTRL_EXT);
	ctrl_ext |= E1000_CTRL_EXT_RO_DIS;
	ew32(CTRL_EXT, ctrl_ext);

	/* Clear all of the statistics registers (clear on read).  It is
	 * important that we do this after we have tried to establish link
	 * because the symbol error count will increment wildly if there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_ich8lan(hw);

	return ret_val;
}