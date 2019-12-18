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
struct tegra_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_INT_MASK ; 
 int i2c_readl (struct tegra_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_writel (struct tegra_i2c_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_i2c_mask_irq(struct tegra_i2c_dev *i2c_dev, u32 mask)
{
	u32 int_mask;

	int_mask = i2c_readl(i2c_dev, I2C_INT_MASK) & ~mask;
	i2c_writel(i2c_dev, int_mask, I2C_INT_MASK);
}