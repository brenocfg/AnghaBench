#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  (* rar_set ) (struct e1000_hw*,scalar_t__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {scalar_t__ type; TYPE_4__ ops; } ;
struct TYPE_7__ {scalar_t__ (* read ) (struct e1000_hw*,int,int,int*) ;} ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_6__ {scalar_t__ func; } ;
struct e1000_hw {TYPE_5__ mac; TYPE_3__ nvm; TYPE_1__ bus; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ALT_MAC_ADDRESS_OFFSET_LAN1 ; 
 scalar_t__ E1000_ALT_MAC_ADDRESS_OFFSET_LAN2 ; 
 scalar_t__ E1000_ALT_MAC_ADDRESS_OFFSET_LAN3 ; 
 scalar_t__ E1000_FUNC_1 ; 
 scalar_t__ E1000_FUNC_2 ; 
 scalar_t__ E1000_FUNC_3 ; 
 int ETH_ALEN ; 
 int NVM_ALT_MAC_ADDR_PTR ; 
 scalar_t__ e1000_82580 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ is_multicast_ether_addr (scalar_t__*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int,int,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,scalar_t__*,int /*<<< orphan*/ ) ; 

s32 igb_check_alt_mac_addr(struct e1000_hw *hw)
{
	u32 i;
	s32 ret_val = 0;
	u16 offset, nvm_alt_mac_addr_offset, nvm_data;
	u8 alt_mac_addr[ETH_ALEN];

	/* Alternate MAC address is handled by the option ROM for 82580
	 * and newer. SW support not required.
	 */
	if (hw->mac.type >= e1000_82580)
		goto out;

	ret_val = hw->nvm.ops.read(hw, NVM_ALT_MAC_ADDR_PTR, 1,
				 &nvm_alt_mac_addr_offset);
	if (ret_val) {
		hw_dbg("NVM Read Error\n");
		goto out;
	}

	if ((nvm_alt_mac_addr_offset == 0xFFFF) ||
	    (nvm_alt_mac_addr_offset == 0x0000))
		/* There is no Alternate MAC Address */
		goto out;

	if (hw->bus.func == E1000_FUNC_1)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN1;
	if (hw->bus.func == E1000_FUNC_2)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN2;

	if (hw->bus.func == E1000_FUNC_3)
		nvm_alt_mac_addr_offset += E1000_ALT_MAC_ADDRESS_OFFSET_LAN3;
	for (i = 0; i < ETH_ALEN; i += 2) {
		offset = nvm_alt_mac_addr_offset + (i >> 1);
		ret_val = hw->nvm.ops.read(hw, offset, 1, &nvm_data);
		if (ret_val) {
			hw_dbg("NVM Read Error\n");
			goto out;
		}

		alt_mac_addr[i] = (u8)(nvm_data & 0xFF);
		alt_mac_addr[i + 1] = (u8)(nvm_data >> 8);
	}

	/* if multicast bit is set, the alternate address will not be used */
	if (is_multicast_ether_addr(alt_mac_addr)) {
		hw_dbg("Ignoring Alternate Mac Address with MC bit set\n");
		goto out;
	}

	/* We have a valid alternate MAC address, and we want to treat it the
	 * same as the normal permanent MAC address stored by the HW into the
	 * RAR. Do this by mapping this address into RAR0.
	 */
	hw->mac.ops.rar_set(hw, alt_mac_addr, 0);

out:
	return ret_val;
}