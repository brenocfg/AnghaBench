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

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_I2CCTL (struct ixgbe_hw*) ; 
 int IXGBE_I2C_BB_EN (struct ixgbe_hw*) ; 
 int IXGBE_I2C_CLK_OE_N_EN (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OE_N_EN (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_T_BUF ; 
 int /*<<< orphan*/  IXGBE_I2C_T_SU_STO ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_set_i2c_data (struct ixgbe_hw*,int*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_i2c_stop(struct ixgbe_hw *hw)
{
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);
	u32 clk_oe_bit = IXGBE_I2C_CLK_OE_N_EN(hw);
	u32 bb_en_bit = IXGBE_I2C_BB_EN(hw);

	/* Stop condition must begin with data low and clock high */
	ixgbe_set_i2c_data(hw, &i2cctl, 0);
	ixgbe_raise_i2c_clk(hw, &i2cctl);

	/* Setup time for stop condition (4us) */
	udelay(IXGBE_I2C_T_SU_STO);

	ixgbe_set_i2c_data(hw, &i2cctl, 1);

	/* bus free time between stop and start (4.7us)*/
	udelay(IXGBE_I2C_T_BUF);

	if (bb_en_bit || data_oe_bit || clk_oe_bit) {
		i2cctl &= ~bb_en_bit;
		i2cctl |= data_oe_bit | clk_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	}
}