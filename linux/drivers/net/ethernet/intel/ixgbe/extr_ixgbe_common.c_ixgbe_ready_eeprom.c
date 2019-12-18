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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_EEPROM_MAX_RETRY_SPI ; 
 int /*<<< orphan*/  IXGBE_EEPROM_OPCODE_BITS ; 
 int /*<<< orphan*/  IXGBE_EEPROM_RDSR_OPCODE_SPI ; 
 int IXGBE_EEPROM_STATUS_RDY_SPI ; 
 int /*<<< orphan*/  IXGBE_ERR_EEPROM ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_shift_in_eeprom_bits (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_shift_out_eeprom_bits (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_standby_eeprom (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbe_ready_eeprom(struct ixgbe_hw *hw)
{
	u16 i;
	u8 spi_stat_reg;

	/*
	 * Read "Status Register" repeatedly until the LSB is cleared.  The
	 * EEPROM will signal that the command has been completed by clearing
	 * bit 0 of the internal status register.  If it's not cleared within
	 * 5 milliseconds, then error out.
	 */
	for (i = 0; i < IXGBE_EEPROM_MAX_RETRY_SPI; i += 5) {
		ixgbe_shift_out_eeprom_bits(hw, IXGBE_EEPROM_RDSR_OPCODE_SPI,
					    IXGBE_EEPROM_OPCODE_BITS);
		spi_stat_reg = (u8)ixgbe_shift_in_eeprom_bits(hw, 8);
		if (!(spi_stat_reg & IXGBE_EEPROM_STATUS_RDY_SPI))
			break;

		udelay(5);
		ixgbe_standby_eeprom(hw);
	}

	/*
	 * On some parts, SPI write time could vary from 0-20mSec on 3.3V
	 * devices (and only 0-5mSec on 5V devices)
	 */
	if (i >= IXGBE_EEPROM_MAX_RETRY_SPI) {
		hw_dbg(hw, "SPI EEPROM Status error\n");
		return IXGBE_ERR_EEPROM;
	}

	return 0;
}