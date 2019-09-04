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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 int /*<<< orphan*/  IXGBE_EEC (struct ixgbe_hw*) ; 
 scalar_t__ IXGBE_EEC_DI ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_lower_eeprom_clk (struct ixgbe_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  ixgbe_raise_eeprom_clk (struct ixgbe_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ixgbe_shift_out_eeprom_bits(struct ixgbe_hw *hw, u16 data,
					u16 count)
{
	u32 eec;
	u32 mask;
	u32 i;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	/*
	 * Mask is used to shift "count" bits of "data" out to the EEPROM
	 * one bit at a time.  Determine the starting bit based on count
	 */
	mask = BIT(count - 1);

	for (i = 0; i < count; i++) {
		/*
		 * A "1" is shifted out to the EEPROM by setting bit "DI" to a
		 * "1", and then raising and then lowering the clock (the SK
		 * bit controls the clock input to the EEPROM).  A "0" is
		 * shifted out to the EEPROM by setting "DI" to "0" and then
		 * raising and then lowering the clock.
		 */
		if (data & mask)
			eec |= IXGBE_EEC_DI;
		else
			eec &= ~IXGBE_EEC_DI;

		IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
		IXGBE_WRITE_FLUSH(hw);

		udelay(1);

		ixgbe_raise_eeprom_clk(hw, &eec);
		ixgbe_lower_eeprom_clk(hw, &eec);

		/*
		 * Shift mask to signify next bit of data to shift in to the
		 * EEPROM
		 */
		mask = mask >> 1;
	}

	/* We leave the "DI" bit set to "0" when we leave this routine. */
	eec &= ~IXGBE_EEC_DI;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);
}