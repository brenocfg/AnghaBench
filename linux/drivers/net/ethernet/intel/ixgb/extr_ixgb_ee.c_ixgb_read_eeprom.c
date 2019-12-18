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
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_READ_OPCODE ; 
 int /*<<< orphan*/  ixgb_setup_eeprom (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_shift_in_bits (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_shift_out_bits (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgb_standby_eeprom (struct ixgb_hw*) ; 

u16
ixgb_read_eeprom(struct ixgb_hw *hw,
		  u16 offset)
{
	u16 data;

	/*  Prepare the EEPROM for reading  */
	ixgb_setup_eeprom(hw);

	/*  Send the READ command (opcode + addr)  */
	ixgb_shift_out_bits(hw, EEPROM_READ_OPCODE, 3);
	/*
	 * We have a 64 word EEPROM, there are 6 address bits
	 */
	ixgb_shift_out_bits(hw, offset, 6);

	/*  Read the data  */
	data = ixgb_shift_in_bits(hw);

	/*  End this read operation  */
	ixgb_standby_eeprom(hw);

	return data;
}