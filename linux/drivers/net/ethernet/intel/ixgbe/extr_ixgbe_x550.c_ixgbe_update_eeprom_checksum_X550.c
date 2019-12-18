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
struct ixgbe_hw {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EEPROM_CHECKSUM ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int ixgbe_calc_eeprom_checksum_X550 (struct ixgbe_hw*) ; 
 int ixgbe_read_ee_hostif_X550 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int ixgbe_update_flash_X550 (struct ixgbe_hw*) ; 
 int ixgbe_write_ee_hostif_X550 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s32 ixgbe_update_eeprom_checksum_X550(struct ixgbe_hw *hw)
{
	s32 status;
	u16 checksum = 0;

	/* Read the first word from the EEPROM. If this times out or fails, do
	 * not continue or we could be in for a very long wait while every
	 * EEPROM read fails
	 */
	status = ixgbe_read_ee_hostif_X550(hw, 0, &checksum);
	if (status) {
		hw_dbg(hw, "EEPROM read failed\n");
		return status;
	}

	status = ixgbe_calc_eeprom_checksum_X550(hw);
	if (status < 0)
		return status;

	checksum = (u16)(status & 0xffff);

	status = ixgbe_write_ee_hostif_X550(hw, IXGBE_EEPROM_CHECKSUM,
					    checksum);
	if (status)
		return status;

	status = ixgbe_update_flash_X550(hw);

	return status;
}