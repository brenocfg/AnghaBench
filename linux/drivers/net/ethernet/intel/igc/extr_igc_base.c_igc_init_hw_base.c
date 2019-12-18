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
typedef  scalar_t__ u16 ;
struct igc_mac_info {scalar_t__ rar_entry_count; scalar_t__ mta_reg_count; scalar_t__ uta_reg_count; } ;
struct igc_hw {struct igc_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_MTA ; 
 int /*<<< orphan*/  IGC_UTA ; 
 int /*<<< orphan*/  array_wr32 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int /*<<< orphan*/  igc_clear_hw_cntrs_base (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_init_rx_addrs (struct igc_hw*,scalar_t__) ; 
 int /*<<< orphan*/  igc_setup_link (struct igc_hw*) ; 

__attribute__((used)) static s32 igc_init_hw_base(struct igc_hw *hw)
{
	struct igc_mac_info *mac = &hw->mac;
	u16 i, rar_count = mac->rar_entry_count;
	s32 ret_val = 0;

	/* Setup the receive address */
	igc_init_rx_addrs(hw, rar_count);

	/* Zero out the Multicast HASH table */
	hw_dbg("Zeroing the MTA\n");
	for (i = 0; i < mac->mta_reg_count; i++)
		array_wr32(IGC_MTA, i, 0);

	/* Zero out the Unicast HASH table */
	hw_dbg("Zeroing the UTA\n");
	for (i = 0; i < mac->uta_reg_count; i++)
		array_wr32(IGC_UTA, i, 0);

	/* Setup link and flow control */
	ret_val = igc_setup_link(hw);

	/* Clear all of the statistics registers (clear on read).  It is
	 * important that we do this after we have tried to establish link
	 * because the symbol error count will increment wildly if there
	 * is no link.
	 */
	igc_clear_hw_cntrs_base(hw);

	return ret_val;
}