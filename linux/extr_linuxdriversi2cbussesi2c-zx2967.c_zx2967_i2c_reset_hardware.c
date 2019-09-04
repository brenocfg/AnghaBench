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
struct zx2967_i2c {int clk_freq; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int I2C_FIFO_MAX ; 
 int I2C_IRQ_MSK_ENABLE ; 
 int I2C_MASTER ; 
 int /*<<< orphan*/  REG_CLK_DIV_FS ; 
 int /*<<< orphan*/  REG_CLK_DIV_HS ; 
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  REG_RDCONF ; 
 int /*<<< orphan*/  REG_WRCONF ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_i2c_flush_fifos (struct zx2967_i2c*) ; 
 int /*<<< orphan*/  zx2967_i2c_writel (struct zx2967_i2c*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx2967_i2c_reset_hardware(struct zx2967_i2c *i2c)
{
	u32 val;
	u32 clk_div;

	val = I2C_MASTER | I2C_IRQ_MSK_ENABLE;
	zx2967_i2c_writel(i2c, val, REG_CMD);

	clk_div = clk_get_rate(i2c->clk) / i2c->clk_freq - 1;
	zx2967_i2c_writel(i2c, clk_div, REG_CLK_DIV_FS);
	zx2967_i2c_writel(i2c, clk_div, REG_CLK_DIV_HS);

	zx2967_i2c_writel(i2c, I2C_FIFO_MAX - 1, REG_WRCONF);
	zx2967_i2c_writel(i2c, I2C_FIFO_MAX - 1, REG_RDCONF);
	zx2967_i2c_writel(i2c, 1, REG_RDCONF);

	zx2967_i2c_flush_fifos(i2c);

	return 0;
}