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
 int /*<<< orphan*/  IXGBE_ERR_I2C ; 
 int /*<<< orphan*/  IXGBE_I2CCTL (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OE_N_EN (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OUT (struct ixgbe_hw*) ; 
 int IXGBE_I2C_T_HIGH ; 
 int IXGBE_I2C_T_LOW ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int ixgbe_get_i2c_data (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_lower_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 ixgbe_get_i2c_ack(struct ixgbe_hw *hw)
{
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);
	s32 status = 0;
	u32 i = 0;
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	u32 timeout = 10;
	bool ack = true;

	if (data_oe_bit) {
		i2cctl |= IXGBE_I2C_DATA_OUT(hw);
		i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	}
	ixgbe_raise_i2c_clk(hw, &i2cctl);

	/* Minimum high period of clock is 4us */
	udelay(IXGBE_I2C_T_HIGH);

	/* Poll for ACK.  Note that ACK in I2C spec is
	 * transition from 1 to 0 */
	for (i = 0; i < timeout; i++) {
		i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
		ack = ixgbe_get_i2c_data(hw, &i2cctl);

		udelay(1);
		if (ack == 0)
			break;
	}

	if (ack == 1) {
		hw_dbg(hw, "I2C ack was not received.\n");
		status = IXGBE_ERR_I2C;
	}

	ixgbe_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	udelay(IXGBE_I2C_T_LOW);

	return status;
}