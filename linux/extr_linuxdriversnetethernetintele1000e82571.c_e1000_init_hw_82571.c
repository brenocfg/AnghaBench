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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ (* setup_link ) (struct e1000_hw*) ;int /*<<< orphan*/  (* clear_vfta ) (struct e1000_hw*) ;scalar_t__ (* id_led_init ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {scalar_t__ rar_entry_count; scalar_t__ mta_reg_count; int type; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int E1000_GCR_L1_ACT_WITHOUT_L0S_RX ; 
 int /*<<< orphan*/  E1000_MTA ; 
 int E1000_TXDCTL_COUNT_DESC ; 
 int E1000_TXDCTL_FULL_TX_DESC_WB ; 
 int E1000_TXDCTL_WTHRESH ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GCR ; 
 int /*<<< orphan*/  TXDCTL (int) ; 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_initialize_hw_bits_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_enable_tx_pkt_filtering (struct e1000_hw*) ; 
 scalar_t__ e1000e_get_laa_state_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_init_rx_addrs (struct e1000_hw*,scalar_t__) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 scalar_t__ stub3 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_hw_82571(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 reg_data;
	s32 ret_val;
	u16 i, rar_count = mac->rar_entry_count;

	e1000_initialize_hw_bits_82571(hw);

	/* Initialize identification LED */
	ret_val = mac->ops.id_led_init(hw);
	/* An error is not fatal and we should not stop init due to this */
	if (ret_val)
		e_dbg("Error initializing identification LED\n");

	/* Disabling VLAN filtering */
	e_dbg("Initializing the IEEE VLAN\n");
	mac->ops.clear_vfta(hw);

	/* Setup the receive address.
	 * If, however, a locally administered address was assigned to the
	 * 82571, we must reserve a RAR for it to work around an issue where
	 * resetting one port will reload the MAC on the other port.
	 */
	if (e1000e_get_laa_state_82571(hw))
		rar_count--;
	e1000e_init_rx_addrs(hw, rar_count);

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	for (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);

	/* Setup link and flow control */
	ret_val = mac->ops.setup_link(hw);

	/* Set the transmit descriptor write-back policy */
	reg_data = er32(TXDCTL(0));
	reg_data = ((reg_data & ~E1000_TXDCTL_WTHRESH) |
		    E1000_TXDCTL_FULL_TX_DESC_WB | E1000_TXDCTL_COUNT_DESC);
	ew32(TXDCTL(0), reg_data);

	/* ...for both queues. */
	switch (mac->type) {
	case e1000_82573:
		e1000e_enable_tx_pkt_filtering(hw);
		/* fall through */
	case e1000_82574:
	case e1000_82583:
		reg_data = er32(GCR);
		reg_data |= E1000_GCR_L1_ACT_WITHOUT_L0S_RX;
		ew32(GCR, reg_data);
		break;
	default:
		reg_data = er32(TXDCTL(1));
		reg_data = ((reg_data & ~E1000_TXDCTL_WTHRESH) |
			    E1000_TXDCTL_FULL_TX_DESC_WB |
			    E1000_TXDCTL_COUNT_DESC);
		ew32(TXDCTL(1), reg_data);
		break;
	}

	/* Clear all of the statistics registers (clear on read).  It is
	 * important that we do this after we have tried to establish link
	 * because the symbol error count will increment wildly if there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_82571(hw);

	return ret_val;
}