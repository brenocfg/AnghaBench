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
struct tegra_i2c_dev {int /*<<< orphan*/  bus_clk_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_CNFG ; 
 int I2C_CNFG_PACKET_MODE_EN ; 
 int i2c_readl (struct tegra_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct tegra_i2c_dev*,int,int /*<<< orphan*/ ) ; 
 int tegra_i2c_wait_for_config_load (struct tegra_i2c_dev*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_i2c_disable_packet_mode(struct tegra_i2c_dev *i2c_dev)
{
	u32 cnfg;

	/*
	 * NACK interrupt is generated before the I2C controller generates
	 * the STOP condition on the bus. So wait for 2 clock periods
	 * before disabling the controller so that the STOP condition has
	 * been delivered properly.
	 */
	udelay(DIV_ROUND_UP(2 * 1000000, i2c_dev->bus_clk_rate));

	cnfg = i2c_readl(i2c_dev, I2C_CNFG);
	if (cnfg & I2C_CNFG_PACKET_MODE_EN)
		i2c_writel(i2c_dev, cnfg & ~I2C_CNFG_PACKET_MODE_EN, I2C_CNFG);

	return tegra_i2c_wait_for_config_load(i2c_dev);
}