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
struct tegra_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ tegra_i2c_reg_addr (struct tegra_i2c_dev*,unsigned long) ; 

__attribute__((used)) static u32 i2c_readl(struct tegra_i2c_dev *i2c_dev, unsigned long reg)
{
	return readl(i2c_dev->base + tegra_i2c_reg_addr(i2c_dev, reg));
}