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
struct tegra_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVC_CTRL_REG1 ; 
 int /*<<< orphan*/  DVC_CTRL_REG1_INTR_EN ; 
 int /*<<< orphan*/  DVC_CTRL_REG3 ; 
 int /*<<< orphan*/  DVC_CTRL_REG3_I2C_DONE_INTR_EN ; 
 int /*<<< orphan*/  DVC_CTRL_REG3_SW_PROG ; 
 int /*<<< orphan*/  dvc_readl (struct tegra_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvc_writel (struct tegra_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dvc_init(struct tegra_i2c_dev *i2c_dev)
{
	u32 val;

	val = dvc_readl(i2c_dev, DVC_CTRL_REG3);
	val |= DVC_CTRL_REG3_SW_PROG;
	val |= DVC_CTRL_REG3_I2C_DONE_INTR_EN;
	dvc_writel(i2c_dev, val, DVC_CTRL_REG3);

	val = dvc_readl(i2c_dev, DVC_CTRL_REG1);
	val |= DVC_CTRL_REG1_INTR_EN;
	dvc_writel(i2c_dev, val, DVC_CTRL_REG1);
}