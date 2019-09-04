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
typedef  int u16 ;
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EECD ; 
 int IXGB_EECD_DI ; 
 int IXGB_EECD_DO ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_lower_clock (struct ixgb_hw*,int*) ; 
 int /*<<< orphan*/  ixgb_raise_clock (struct ixgb_hw*,int*) ; 

__attribute__((used)) static u16
ixgb_shift_in_bits(struct ixgb_hw *hw)
{
	u32 eecd_reg;
	u32 i;
	u16 data;

	/* In order to read a register from the EEPROM, we need to shift 16 bits
	 * in from the EEPROM. Bits are "shifted in" by raising the clock input to
	 * the EEPROM (setting the SK bit), and then reading the value of the "DO"
	 * bit.  During this "shifting in" process the "DI" bit should always be
	 * clear..
	 */

	eecd_reg = IXGB_READ_REG(hw, EECD);

	eecd_reg &= ~(IXGB_EECD_DO | IXGB_EECD_DI);
	data = 0;

	for (i = 0; i < 16; i++) {
		data = data << 1;
		ixgb_raise_clock(hw, &eecd_reg);

		eecd_reg = IXGB_READ_REG(hw, EECD);

		eecd_reg &= ~(IXGB_EECD_DI);
		if (eecd_reg & IXGB_EECD_DO)
			data |= 1;

		ixgb_lower_clock(hw, &eecd_reg);
	}

	return data;
}