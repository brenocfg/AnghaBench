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
struct e1000_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_FLUPD_I210 ; 
 int E1000_ERR_NVM ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int igb_pool_flash_update_done_i210 (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 igb_update_flash_i210(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u32 flup;

	ret_val = igb_pool_flash_update_done_i210(hw);
	if (ret_val == -E1000_ERR_NVM) {
		hw_dbg("Flash update time out\n");
		goto out;
	}

	flup = rd32(E1000_EECD) | E1000_EECD_FLUPD_I210;
	wr32(E1000_EECD, flup);

	ret_val = igb_pool_flash_update_done_i210(hw);
	if (ret_val)
		hw_dbg("Flash update time out\n");
	else
		hw_dbg("Flash update complete\n");

out:
	return ret_val;
}