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
struct exynos5_i2c {scalar_t__ regs; } ;

/* Variables and functions */
 int HSI2C_AUTO_MODE ; 
 int HSI2C_CMD_READ_DATA ; 
 int HSI2C_CMD_SEND_STOP ; 
 scalar_t__ HSI2C_CONF ; 
 scalar_t__ HSI2C_CTL ; 
 scalar_t__ HSI2C_MANUAL_CMD ; 
 int HSI2C_RXCHON ; 
 int /*<<< orphan*/  exynos5_i2c_wait_bus_idle (struct exynos5_i2c*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos5_i2c_bus_recover(struct exynos5_i2c *i2c)
{
	u32 val;

	val = readl(i2c->regs + HSI2C_CTL) | HSI2C_RXCHON;
	writel(val, i2c->regs + HSI2C_CTL);
	val = readl(i2c->regs + HSI2C_CONF) & ~HSI2C_AUTO_MODE;
	writel(val, i2c->regs + HSI2C_CONF);

	/*
	 * Specification says master should send nine clock pulses. It can be
	 * emulated by sending manual read command (nine pulses for read eight
	 * bits + one pulse for NACK).
	 */
	writel(HSI2C_CMD_READ_DATA, i2c->regs + HSI2C_MANUAL_CMD);
	exynos5_i2c_wait_bus_idle(i2c);
	writel(HSI2C_CMD_SEND_STOP, i2c->regs + HSI2C_MANUAL_CMD);
	exynos5_i2c_wait_bus_idle(i2c);

	val = readl(i2c->regs + HSI2C_CTL) & ~HSI2C_RXCHON;
	writel(val, i2c->regs + HSI2C_CTL);
	val = readl(i2c->regs + HSI2C_CONF) | HSI2C_AUTO_MODE;
	writel(val, i2c->regs + HSI2C_CONF);
}