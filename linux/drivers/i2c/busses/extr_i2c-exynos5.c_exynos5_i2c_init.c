#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct exynos5_i2c {scalar_t__ op_clock; scalar_t__ regs; TYPE_1__ adap; } ;

/* Variables and functions */
 scalar_t__ HSI2C_ADDR ; 
 int HSI2C_AUTO_MODE ; 
 scalar_t__ HSI2C_CONF ; 
 scalar_t__ HSI2C_CTL ; 
 int HSI2C_FUNC_MODE_I2C ; 
 int HSI2C_HS_MODE ; 
 scalar_t__ HSI2C_HS_TX_CLOCK ; 
 int HSI2C_MASTER ; 
 int HSI2C_MASTER_ID (int /*<<< orphan*/ ) ; 
 scalar_t__ HSI2C_TIMEOUT ; 
 int HSI2C_TIMEOUT_EN ; 
 scalar_t__ HSI2C_TRAILIG_CTL ; 
 int HSI2C_TRAILING_COUNT ; 
 int /*<<< orphan*/  MASTER_ID (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos5_i2c_init(struct exynos5_i2c *i2c)
{
	u32 i2c_conf = readl(i2c->regs + HSI2C_CONF);
	u32 i2c_timeout = readl(i2c->regs + HSI2C_TIMEOUT);

	/* Clear to disable Timeout */
	i2c_timeout &= ~HSI2C_TIMEOUT_EN;
	writel(i2c_timeout, i2c->regs + HSI2C_TIMEOUT);

	writel((HSI2C_FUNC_MODE_I2C | HSI2C_MASTER),
					i2c->regs + HSI2C_CTL);
	writel(HSI2C_TRAILING_COUNT, i2c->regs + HSI2C_TRAILIG_CTL);

	if (i2c->op_clock >= HSI2C_HS_TX_CLOCK) {
		writel(HSI2C_MASTER_ID(MASTER_ID(i2c->adap.nr)),
					i2c->regs + HSI2C_ADDR);
		i2c_conf |= HSI2C_HS_MODE;
	}

	writel(i2c_conf | HSI2C_AUTO_MODE, i2c->regs + HSI2C_CONF);
}