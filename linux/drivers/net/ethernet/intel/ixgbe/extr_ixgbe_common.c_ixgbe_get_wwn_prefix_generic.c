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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,int,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_ALT_SAN_MAC_ADDR_BLK_PTR ; 
 int IXGBE_ALT_SAN_MAC_ADDR_CAPS_ALTWWN ; 
 int IXGBE_ALT_SAN_MAC_ADDR_CAPS_OFFSET ; 
 int IXGBE_ALT_SAN_MAC_ADDR_WWNN_OFFSET ; 
 int IXGBE_ALT_SAN_MAC_ADDR_WWPN_OFFSET ; 
 int /*<<< orphan*/  hw_err (struct ixgbe_hw*,char*,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int,int*) ; 

s32 ixgbe_get_wwn_prefix_generic(struct ixgbe_hw *hw, u16 *wwnn_prefix,
					u16 *wwpn_prefix)
{
	u16 offset, caps;
	u16 alt_san_mac_blk_offset;

	/* clear output first */
	*wwnn_prefix = 0xFFFF;
	*wwpn_prefix = 0xFFFF;

	/* check if alternative SAN MAC is supported */
	offset = IXGBE_ALT_SAN_MAC_ADDR_BLK_PTR;
	if (hw->eeprom.ops.read(hw, offset, &alt_san_mac_blk_offset))
		goto wwn_prefix_err;

	if ((alt_san_mac_blk_offset == 0) ||
	    (alt_san_mac_blk_offset == 0xFFFF))
		return 0;

	/* check capability in alternative san mac address block */
	offset = alt_san_mac_blk_offset + IXGBE_ALT_SAN_MAC_ADDR_CAPS_OFFSET;
	if (hw->eeprom.ops.read(hw, offset, &caps))
		goto wwn_prefix_err;
	if (!(caps & IXGBE_ALT_SAN_MAC_ADDR_CAPS_ALTWWN))
		return 0;

	/* get the corresponding prefix for WWNN/WWPN */
	offset = alt_san_mac_blk_offset + IXGBE_ALT_SAN_MAC_ADDR_WWNN_OFFSET;
	if (hw->eeprom.ops.read(hw, offset, wwnn_prefix))
		hw_err(hw, "eeprom read at offset %d failed\n", offset);

	offset = alt_san_mac_blk_offset + IXGBE_ALT_SAN_MAC_ADDR_WWPN_OFFSET;
	if (hw->eeprom.ops.read(hw, offset, wwpn_prefix))
		goto wwn_prefix_err;

	return 0;

wwn_prefix_err:
	hw_err(hw, "eeprom read at offset %d failed\n", offset);
	return 0;
}