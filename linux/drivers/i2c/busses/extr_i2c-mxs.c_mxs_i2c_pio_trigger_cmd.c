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
struct mxs_i2c_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MXS_I2C_CTRL0 ; 
 int /*<<< orphan*/  MXS_I2C_CTRL0_RUN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_i2c_pio_trigger_cmd(struct mxs_i2c_dev *i2c, u32 cmd)
{
	u32 reg;

	writel(cmd, i2c->regs + MXS_I2C_CTRL0);

	/* readback makes sure the write is latched into hardware */
	reg = readl(i2c->regs + MXS_I2C_CTRL0);
	reg |= MXS_I2C_CTRL0_RUN;
	writel(reg, i2c->regs + MXS_I2C_CTRL0);
}