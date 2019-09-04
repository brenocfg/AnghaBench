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
struct e1000_eeprom_info {scalar_t__ type; int /*<<< orphan*/  delay_usec; } ;
struct e1000_hw {struct e1000_eeprom_info eeprom; } ;

/* Variables and functions */
 int E1000_EECD_DI ; 
 int E1000_EECD_DO ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  EECD ; 
 scalar_t__ e1000_eeprom_microwire ; 
 scalar_t__ e1000_eeprom_spi ; 
 int /*<<< orphan*/  e1000_lower_ee_clk (struct e1000_hw*,int*) ; 
 int /*<<< orphan*/  e1000_raise_ee_clk (struct e1000_hw*,int*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_shift_out_ee_bits(struct e1000_hw *hw, u16 data, u16 count)
{
	struct e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd;
	u32 mask;

	/* We need to shift "count" bits out to the EEPROM. So, value in the
	 * "data" parameter will be shifted out to the EEPROM one bit at a time.
	 * In order to do this, "data" must be broken down into bits.
	 */
	mask = 0x01 << (count - 1);
	eecd = er32(EECD);
	if (eeprom->type == e1000_eeprom_microwire)
		eecd &= ~E1000_EECD_DO;
	else if (eeprom->type == e1000_eeprom_spi)
		eecd |= E1000_EECD_DO;

	do {
		/* A "1" is shifted out to the EEPROM by setting bit "DI" to a
		 * "1", and then raising and then lowering the clock (the SK bit
		 * controls the clock input to the EEPROM).  A "0" is shifted
		 * out to the EEPROM by setting "DI" to "0" and then raising and
		 * then lowering the clock.
		 */
		eecd &= ~E1000_EECD_DI;

		if (data & mask)
			eecd |= E1000_EECD_DI;

		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();

		udelay(eeprom->delay_usec);

		e1000_raise_ee_clk(hw, &eecd);
		e1000_lower_ee_clk(hw, &eecd);

		mask = mask >> 1;

	} while (mask);

	/* We leave the "DI" bit set to "0" when we leave this routine. */
	eecd &= ~E1000_EECD_DI;
	ew32(EECD, eecd);
}