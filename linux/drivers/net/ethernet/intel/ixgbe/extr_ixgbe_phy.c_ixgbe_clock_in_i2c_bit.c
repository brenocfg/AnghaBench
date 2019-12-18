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
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_I2CCTL (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OE_N_EN (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OUT (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_T_HIGH ; 
 int /*<<< orphan*/  IXGBE_I2C_T_LOW ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int ixgbe_get_i2c_data (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_lower_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_clock_in_i2c_bit(struct ixgbe_hw *hw, bool *data)
{
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	if (data_oe_bit) {
		i2cctl |= IXGBE_I2C_DATA_OUT(hw);
		i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	}
	ixgbe_raise_i2c_clk(hw, &i2cctl);

	/* Minimum high period of clock is 4us */
	udelay(IXGBE_I2C_T_HIGH);

	i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	*data = ixgbe_get_i2c_data(hw, &i2cctl);

	ixgbe_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	udelay(IXGBE_I2C_T_LOW);

	return 0;
}