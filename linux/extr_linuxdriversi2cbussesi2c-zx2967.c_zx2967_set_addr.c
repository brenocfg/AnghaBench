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
typedef  int u16 ;
struct zx2967_i2c {int dummy; } ;

/* Variables and functions */
 int I2C_ADDR_HI_MASK ; 
 int I2C_ADDR_HI_SHIFT ; 
 int I2C_ADDR_LOW_MASK ; 
 int I2C_ADDR_LOW_SHIFT ; 
 int I2C_ADDR_MODE_TEN ; 
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  REG_DEVADDR_H ; 
 int /*<<< orphan*/  REG_DEVADDR_L ; 
 int zx2967_i2c_readl (struct zx2967_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_i2c_writel (struct zx2967_i2c*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx2967_set_addr(struct zx2967_i2c *i2c, u16 addr)
{
	u16 val;

	val = (addr >> I2C_ADDR_LOW_SHIFT) & I2C_ADDR_LOW_MASK;
	zx2967_i2c_writel(i2c, val, REG_DEVADDR_L);

	val = (addr >> I2C_ADDR_HI_SHIFT) & I2C_ADDR_HI_MASK;
	zx2967_i2c_writel(i2c, val, REG_DEVADDR_H);
	if (val)
		val = zx2967_i2c_readl(i2c, REG_CMD) | I2C_ADDR_MODE_TEN;
	else
		val = zx2967_i2c_readl(i2c, REG_CMD) & ~I2C_ADDR_MODE_TEN;
	zx2967_i2c_writel(i2c, val, REG_CMD);
}