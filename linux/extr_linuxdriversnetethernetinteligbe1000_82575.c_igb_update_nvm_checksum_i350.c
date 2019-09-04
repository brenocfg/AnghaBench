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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int NVM_82580_LAN_FUNC_OFFSET (int) ; 
 scalar_t__ igb_update_nvm_checksum_with_offset (struct e1000_hw*,int) ; 

__attribute__((used)) static s32 igb_update_nvm_checksum_i350(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u16 j;
	u16 nvm_offset;

	for (j = 0; j < 4; j++) {
		nvm_offset = NVM_82580_LAN_FUNC_OFFSET(j);
		ret_val = igb_update_nvm_checksum_with_offset(hw, nvm_offset);
		if (ret_val != 0)
			goto out;
	}

out:
	return ret_val;
}