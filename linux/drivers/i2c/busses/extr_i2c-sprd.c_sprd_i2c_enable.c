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
struct sprd_i2c {scalar_t__ base; int /*<<< orphan*/  bus_freq; } ;

/* Variables and functions */
 scalar_t__ I2C_CTL ; 
 int I2C_DVD_OPT ; 
 int I2C_EN ; 
 int /*<<< orphan*/  I2C_FIFO_EMPTY_THLD ; 
 int /*<<< orphan*/  I2C_FIFO_FULL_THLD ; 
 int I2C_INT_EN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sprd_i2c_clear_irq (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_reset_fifo (struct sprd_i2c*) ; 
 int /*<<< orphan*/  sprd_i2c_set_clk (struct sprd_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_i2c_set_empty_thld (struct sprd_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_i2c_set_full_thld (struct sprd_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sprd_i2c_enable(struct sprd_i2c *i2c_dev)
{
	u32 tmp = I2C_DVD_OPT;

	writel(tmp, i2c_dev->base + I2C_CTL);

	sprd_i2c_set_full_thld(i2c_dev, I2C_FIFO_FULL_THLD);
	sprd_i2c_set_empty_thld(i2c_dev, I2C_FIFO_EMPTY_THLD);

	sprd_i2c_set_clk(i2c_dev, i2c_dev->bus_freq);
	sprd_i2c_reset_fifo(i2c_dev);
	sprd_i2c_clear_irq(i2c_dev);

	tmp = readl(i2c_dev->base + I2C_CTL);
	writel(tmp | I2C_EN | I2C_INT_EN, i2c_dev->base + I2C_CTL);
}