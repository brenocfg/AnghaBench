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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_I2CCTL (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_BB_EN (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_T_HD_STA ; 
 int /*<<< orphan*/  IXGBE_I2C_T_LOW ; 
 int /*<<< orphan*/  IXGBE_I2C_T_SU_STA ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_lower_i2c_clk (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_set_i2c_data (struct ixgbe_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_i2c_start(struct ixgbe_hw *hw)
{
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));

	i2cctl |= IXGBE_I2C_BB_EN(hw);

	/* Start condition must begin with data and clock high */
	ixgbe_set_i2c_data(hw, &i2cctl, 1);
	ixgbe_raise_i2c_clk(hw, &i2cctl);

	/* Setup time for start condition (4.7us) */
	udelay(IXGBE_I2C_T_SU_STA);

	ixgbe_set_i2c_data(hw, &i2cctl, 0);

	/* Hold time for start condition (4us) */
	udelay(IXGBE_I2C_T_HD_STA);

	ixgbe_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	udelay(IXGBE_I2C_T_LOW);

}