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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aspeed_i2c_get_clk_reg_val (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 aspeed_i2c_25xx_get_clk_reg_val(struct device *dev, u32 divisor)
{
	/*
	 * clk_high and clk_low are each 4 bits wide, so each can hold a max
	 * value of 16 giving a clk_high_low_max of 32.
	 */
	return aspeed_i2c_get_clk_reg_val(dev, GENMASK(3, 0), divisor);
}