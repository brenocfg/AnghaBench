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
struct device {int dummy; } ;

/* Variables and functions */
 int ASPEED_I2CD_TIME_BASE_DIVISOR_MASK ; 
 int ASPEED_I2CD_TIME_SCL_HIGH_MASK ; 
 int ASPEED_I2CD_TIME_SCL_HIGH_SHIFT ; 
 int ASPEED_I2CD_TIME_SCL_LOW_MASK ; 
 int ASPEED_I2CD_TIME_SCL_LOW_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int ilog2 (int) ; 

__attribute__((used)) static u32 aspeed_i2c_get_clk_reg_val(struct device *dev,
				      u32 clk_high_low_mask,
				      u32 divisor)
{
	u32 base_clk_divisor, clk_high_low_max, clk_high, clk_low, tmp;

	/*
	 * SCL_high and SCL_low represent a value 1 greater than what is stored
	 * since a zero divider is meaningless. Thus, the max value each can
	 * store is every bit set + 1. Since SCL_high and SCL_low are added
	 * together (see below), the max value of both is the max value of one
	 * them times two.
	 */
	clk_high_low_max = (clk_high_low_mask + 1) * 2;

	/*
	 * The actual clock frequency of SCL is:
	 *	SCL_freq = APB_freq / (base_freq * (SCL_high + SCL_low))
	 *		 = APB_freq / divisor
	 * where base_freq is a programmable clock divider; its value is
	 *	base_freq = 1 << base_clk_divisor
	 * SCL_high is the number of base_freq clock cycles that SCL stays high
	 * and SCL_low is the number of base_freq clock cycles that SCL stays
	 * low for a period of SCL.
	 * The actual register has a minimum SCL_high and SCL_low minimum of 1;
	 * thus, they start counting at zero. So
	 *	SCL_high = clk_high + 1
	 *	SCL_low	 = clk_low + 1
	 * Thus,
	 *	SCL_freq = APB_freq /
	 *		((1 << base_clk_divisor) * (clk_high + 1 + clk_low + 1))
	 * The documentation recommends clk_high >= clk_high_max / 2 and
	 * clk_low >= clk_low_max / 2 - 1 when possible; this last constraint
	 * gives us the following solution:
	 */
	base_clk_divisor = divisor > clk_high_low_max ?
			ilog2((divisor - 1) / clk_high_low_max) + 1 : 0;

	if (base_clk_divisor > ASPEED_I2CD_TIME_BASE_DIVISOR_MASK) {
		base_clk_divisor = ASPEED_I2CD_TIME_BASE_DIVISOR_MASK;
		clk_low = clk_high_low_mask;
		clk_high = clk_high_low_mask;
		dev_err(dev,
			"clamping clock divider: divider requested, %u, is greater than largest possible divider, %u.\n",
			divisor, (1 << base_clk_divisor) * clk_high_low_max);
	} else {
		tmp = (divisor + (1 << base_clk_divisor) - 1)
				>> base_clk_divisor;
		clk_low = tmp / 2;
		clk_high = tmp - clk_low;

		if (clk_high)
			clk_high--;

		if (clk_low)
			clk_low--;
	}


	return ((clk_high << ASPEED_I2CD_TIME_SCL_HIGH_SHIFT)
		& ASPEED_I2CD_TIME_SCL_HIGH_MASK)
			| ((clk_low << ASPEED_I2CD_TIME_SCL_LOW_SHIFT)
			   & ASPEED_I2CD_TIME_SCL_LOW_MASK)
			| (base_clk_divisor
			   & ASPEED_I2CD_TIME_BASE_DIVISOR_MASK);
}