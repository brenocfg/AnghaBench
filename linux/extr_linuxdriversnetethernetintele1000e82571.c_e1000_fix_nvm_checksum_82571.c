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
typedef  int u16 ;
struct e1000_nvm_info {scalar_t__ type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ e1000_nvm_flash_hw ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,int,int,int*) ; 
 scalar_t__ e1000_write_nvm (struct e1000_hw*,int,int,int*) ; 
 scalar_t__ e1000e_update_nvm_checksum (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_fix_nvm_checksum_82571(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	s32 ret_val;
	u16 data;

	if (nvm->type != e1000_nvm_flash_hw)
		return 0;

	/* Check bit 4 of word 10h.  If it is 0, firmware is done updating
	 * 10h-12h.  Checksum may need to be fixed.
	 */
	ret_val = e1000_read_nvm(hw, 0x10, 1, &data);
	if (ret_val)
		return ret_val;

	if (!(data & 0x10)) {
		/* Read 0x23 and check bit 15.  This bit is a 1
		 * when the checksum has already been fixed.  If
		 * the checksum is still wrong and this bit is a
		 * 1, we need to return bad checksum.  Otherwise,
		 * we need to set this bit to a 1 and update the
		 * checksum.
		 */
		ret_val = e1000_read_nvm(hw, 0x23, 1, &data);
		if (ret_val)
			return ret_val;

		if (!(data & 0x8000)) {
			data |= 0x8000;
			ret_val = e1000_write_nvm(hw, 0x23, 1, &data);
			if (ret_val)
				return ret_val;
			ret_val = e1000e_update_nvm_checksum(hw);
			if (ret_val)
				return ret_val;
		}
	}

	return 0;
}