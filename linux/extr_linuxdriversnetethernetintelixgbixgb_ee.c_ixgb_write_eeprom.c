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
typedef  int /*<<< orphan*/  u16 ;
struct ixgb_hw {scalar_t__ eeprom; } ;
struct ixgb_ee_map_type {int /*<<< orphan*/  init_ctrl_reg_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_EWDS_OPCODE ; 
 int /*<<< orphan*/  EEPROM_EWEN_OPCODE ; 
 int /*<<< orphan*/  EEPROM_ICW1_SIGNATURE_CLEAR ; 
 int /*<<< orphan*/  EEPROM_WRITE_OPCODE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_cleanup_eeprom (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_setup_eeprom (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_shift_out_bits (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgb_standby_eeprom (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_wait_eeprom_command (struct ixgb_hw*) ; 

void
ixgb_write_eeprom(struct ixgb_hw *hw, u16 offset, u16 data)
{
	struct ixgb_ee_map_type *ee_map = (struct ixgb_ee_map_type *)hw->eeprom;

	/* Prepare the EEPROM for writing */
	ixgb_setup_eeprom(hw);

	/*  Send the 9-bit EWEN (write enable) command to the EEPROM (5-bit opcode
	 *  plus 4-bit dummy).  This puts the EEPROM into write/erase mode.
	 */
	ixgb_shift_out_bits(hw, EEPROM_EWEN_OPCODE, 5);
	ixgb_shift_out_bits(hw, 0, 4);

	/*  Prepare the EEPROM  */
	ixgb_standby_eeprom(hw);

	/*  Send the Write command (3-bit opcode + 6-bit addr)  */
	ixgb_shift_out_bits(hw, EEPROM_WRITE_OPCODE, 3);
	ixgb_shift_out_bits(hw, offset, 6);

	/*  Send the data  */
	ixgb_shift_out_bits(hw, data, 16);

	ixgb_wait_eeprom_command(hw);

	/*  Recover from write  */
	ixgb_standby_eeprom(hw);

	/* Send the 9-bit EWDS (write disable) command to the EEPROM (5-bit
	 * opcode plus 4-bit dummy).  This takes the EEPROM out of write/erase
	 * mode.
	 */
	ixgb_shift_out_bits(hw, EEPROM_EWDS_OPCODE, 5);
	ixgb_shift_out_bits(hw, 0, 4);

	/*  Done with writing  */
	ixgb_cleanup_eeprom(hw);

	/* clear the init_ctrl_reg_1 to signify that the cache is invalidated */
	ee_map->init_ctrl_reg_1 = cpu_to_le16(EEPROM_ICW1_SIGNATURE_CLEAR);
}