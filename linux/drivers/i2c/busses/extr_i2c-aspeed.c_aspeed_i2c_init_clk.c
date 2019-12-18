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
struct aspeed_i2c_bus {int (* get_clk_reg_val ) (int /*<<< orphan*/ ,int) ;scalar_t__ base; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_frequency; int /*<<< orphan*/  parent_clk_frequency; } ;

/* Variables and functions */
 int ASPEED_I2CD_TIME_TACST_MASK ; 
 int ASPEED_I2CD_TIME_TBUF_MASK ; 
 int ASPEED_I2CD_TIME_THDSTA_MASK ; 
 scalar_t__ ASPEED_I2C_AC_TIMING_REG1 ; 
 scalar_t__ ASPEED_I2C_AC_TIMING_REG2 ; 
 int ASPEED_NO_TIMEOUT_CTRL ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int aspeed_i2c_init_clk(struct aspeed_i2c_bus *bus)
{
	u32 divisor, clk_reg_val;

	divisor = DIV_ROUND_UP(bus->parent_clk_frequency, bus->bus_frequency);
	clk_reg_val = readl(bus->base + ASPEED_I2C_AC_TIMING_REG1);
	clk_reg_val &= (ASPEED_I2CD_TIME_TBUF_MASK |
			ASPEED_I2CD_TIME_THDSTA_MASK |
			ASPEED_I2CD_TIME_TACST_MASK);
	clk_reg_val |= bus->get_clk_reg_val(bus->dev, divisor);
	writel(clk_reg_val, bus->base + ASPEED_I2C_AC_TIMING_REG1);
	writel(ASPEED_NO_TIMEOUT_CTRL, bus->base + ASPEED_I2C_AC_TIMING_REG2);

	return 0;
}