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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_NVM ; 
 scalar_t__ e1000_pch_spt ; 
 scalar_t__ e1000_read_flash_data_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static s32 e1000_read_flash_byte_ich8lan(struct e1000_hw *hw, u32 offset,
					 u8 *data)
{
	s32 ret_val;
	u16 word = 0;

	/* In SPT, only 32 bits access is supported,
	 * so this function should not be called.
	 */
	if (hw->mac.type >= e1000_pch_spt)
		return -E1000_ERR_NVM;
	else
		ret_val = e1000_read_flash_data_ich8lan(hw, offset, 1, &word);

	if (ret_val)
		return ret_val;

	*data = (u8)word;

	return 0;
}