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
struct TYPE_3__ {scalar_t__ (* write ) (struct igc_hw*,scalar_t__,int,scalar_t__*) ;scalar_t__ (* read ) (struct igc_hw*,scalar_t__,int,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_2__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ NVM_CHECKSUM_REG ; 
 scalar_t__ NVM_SUM ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ stub1 (struct igc_hw*,scalar_t__,int,scalar_t__*) ; 
 scalar_t__ stub2 (struct igc_hw*,scalar_t__,int,scalar_t__*) ; 

s32 igc_update_nvm_checksum(struct igc_hw *hw)
{
	u16 checksum = 0;
	u16 i, nvm_data;
	s32  ret_val;

	for (i = 0; i < NVM_CHECKSUM_REG; i++) {
		ret_val = hw->nvm.ops.read(hw, i, 1, &nvm_data);
		if (ret_val) {
			hw_dbg("NVM Read Error while updating checksum.\n");
			goto out;
		}
		checksum += nvm_data;
	}
	checksum = (u16)NVM_SUM - checksum;
	ret_val = hw->nvm.ops.write(hw, NVM_CHECKSUM_REG, 1, &checksum);
	if (ret_val)
		hw_dbg("NVM Write Error while updating checksum.\n");

out:
	return ret_val;
}