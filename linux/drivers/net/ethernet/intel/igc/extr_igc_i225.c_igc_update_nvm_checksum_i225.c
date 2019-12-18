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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct igc_hw*) ;scalar_t__ (* acquire ) (struct igc_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_2__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ NVM_CHECKSUM_REG ; 
 scalar_t__ NVM_SUM ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igc_read_nvm_eerd (struct igc_hw*,scalar_t__,int,scalar_t__*) ; 
 scalar_t__ igc_update_flash_i225 (struct igc_hw*) ; 
 scalar_t__ igc_write_nvm_srwr (struct igc_hw*,scalar_t__,int,scalar_t__*) ; 
 scalar_t__ stub1 (struct igc_hw*) ; 
 int /*<<< orphan*/  stub2 (struct igc_hw*) ; 
 int /*<<< orphan*/  stub3 (struct igc_hw*) ; 
 int /*<<< orphan*/  stub4 (struct igc_hw*) ; 

__attribute__((used)) static s32 igc_update_nvm_checksum_i225(struct igc_hw *hw)
{
	u16 checksum = 0;
	s32 ret_val = 0;
	u16 i, nvm_data;

	/* Read the first word from the EEPROM. If this times out or fails, do
	 * not continue or we could be in for a very long wait while every
	 * EEPROM read fails
	 */
	ret_val = igc_read_nvm_eerd(hw, 0, 1, &nvm_data);
	if (ret_val) {
		hw_dbg("EEPROM read failed\n");
		goto out;
	}

	ret_val = hw->nvm.ops.acquire(hw);
	if (ret_val)
		goto out;

	/* Do not use hw->nvm.ops.write, hw->nvm.ops.read
	 * because we do not want to take the synchronization
	 * semaphores twice here.
	 */

	for (i = 0; i < NVM_CHECKSUM_REG; i++) {
		ret_val = igc_read_nvm_eerd(hw, i, 1, &nvm_data);
		if (ret_val) {
			hw->nvm.ops.release(hw);
			hw_dbg("NVM Read Error while updating checksum.\n");
			goto out;
		}
		checksum += nvm_data;
	}
	checksum = (u16)NVM_SUM - checksum;
	ret_val = igc_write_nvm_srwr(hw, NVM_CHECKSUM_REG, 1,
				     &checksum);
	if (ret_val) {
		hw->nvm.ops.release(hw);
		hw_dbg("NVM Write Error while updating checksum.\n");
		goto out;
	}

	hw->nvm.ops.release(hw);

	ret_val = igc_update_flash_i225(hw);

out:
	return ret_val;
}