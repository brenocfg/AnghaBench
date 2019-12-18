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
typedef  int u16 ;
struct e1000_eeprom_info {int opcode_bits; int address_bits; int page_size; } ;
struct e1000_hw {struct e1000_eeprom_info eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_EEPROM ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int EEPROM_A8_OPCODE_SPI ; 
 int EEPROM_WREN_OPCODE_SPI ; 
 int EEPROM_WRITE_OPCODE_SPI ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  e1000_shift_out_ee_bits (struct e1000_hw*,int,int) ; 
 scalar_t__ e1000_spi_eeprom_ready (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_standby_eeprom (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_write_eeprom_spi(struct e1000_hw *hw, u16 offset, u16 words,
				  u16 *data)
{
	struct e1000_eeprom_info *eeprom = &hw->eeprom;
	u16 widx = 0;

	while (widx < words) {
		u8 write_opcode = EEPROM_WRITE_OPCODE_SPI;

		if (e1000_spi_eeprom_ready(hw))
			return -E1000_ERR_EEPROM;

		e1000_standby_eeprom(hw);
		cond_resched();

		/*  Send the WRITE ENABLE command (8 bit opcode )  */
		e1000_shift_out_ee_bits(hw, EEPROM_WREN_OPCODE_SPI,
					eeprom->opcode_bits);

		e1000_standby_eeprom(hw);

		/* Some SPI eeproms use the 8th address bit embedded in the
		 * opcode
		 */
		if ((eeprom->address_bits == 8) && (offset >= 128))
			write_opcode |= EEPROM_A8_OPCODE_SPI;

		/* Send the Write command (8-bit opcode + addr) */
		e1000_shift_out_ee_bits(hw, write_opcode, eeprom->opcode_bits);

		e1000_shift_out_ee_bits(hw, (u16)((offset + widx) * 2),
					eeprom->address_bits);

		/* Send the data */

		/* Loop to allow for up to whole page write (32 bytes) of
		 * eeprom
		 */
		while (widx < words) {
			u16 word_out = data[widx];

			word_out = (word_out >> 8) | (word_out << 8);
			e1000_shift_out_ee_bits(hw, word_out, 16);
			widx++;

			/* Some larger eeprom sizes are capable of a 32-byte
			 * PAGE WRITE operation, while the smaller eeproms are
			 * capable of an 8-byte PAGE WRITE operation.  Break the
			 * inner loop to pass new address
			 */
			if ((((offset + widx) * 2) % eeprom->page_size) == 0) {
				e1000_standby_eeprom(hw);
				break;
			}
		}
	}

	return E1000_SUCCESS;
}