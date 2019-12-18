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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct e1000_nvm_info {scalar_t__ type; int /*<<< orphan*/  opcode_bits; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_CS ; 
 int E1000_EECD_SK ; 
 int /*<<< orphan*/  E1000_ERR_NVM ; 
 scalar_t__ NVM_MAX_RETRY_SPI ; 
 int /*<<< orphan*/  NVM_RDSR_OPCODE_SPI ; 
 int NVM_STATUS_RDY_SPI ; 
 scalar_t__ e1000_nvm_eeprom_spi ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igb_shift_in_eec_bits (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  igb_shift_out_eec_bits (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_standby_nvm (struct e1000_hw*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static s32 igb_ready_nvm_eeprom(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(E1000_EECD);
	s32 ret_val = 0;
	u16 timeout = 0;
	u8 spi_stat_reg;


	if (nvm->type == e1000_nvm_eeprom_spi) {
		/* Clear SK and CS */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		wr32(E1000_EECD, eecd);
		wrfl();
		udelay(1);
		timeout = NVM_MAX_RETRY_SPI;

		/* Read "Status Register" repeatedly until the LSB is cleared.
		 * The EEPROM will signal that the command has been completed
		 * by clearing bit 0 of the internal status register.  If it's
		 * not cleared within 'timeout', then error out.
		 */
		while (timeout) {
			igb_shift_out_eec_bits(hw, NVM_RDSR_OPCODE_SPI,
					       hw->nvm.opcode_bits);
			spi_stat_reg = (u8)igb_shift_in_eec_bits(hw, 8);
			if (!(spi_stat_reg & NVM_STATUS_RDY_SPI))
				break;

			udelay(5);
			igb_standby_nvm(hw);
			timeout--;
		}

		if (!timeout) {
			hw_dbg("SPI NVM Status error\n");
			ret_val = -E1000_ERR_NVM;
			goto out;
		}
	}

out:
	return ret_val;
}