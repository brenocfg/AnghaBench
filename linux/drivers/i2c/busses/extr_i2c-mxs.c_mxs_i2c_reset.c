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
struct mxs_i2c_dev {int timing0; int timing1; int timing2; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MXS_I2C_CTRL1_SET ; 
 int MXS_I2C_IRQ_MASK ; 
 scalar_t__ MXS_I2C_TIMING0 ; 
 scalar_t__ MXS_I2C_TIMING1 ; 
 scalar_t__ MXS_I2C_TIMING2 ; 
 int stmp_reset_block (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_i2c_reset(struct mxs_i2c_dev *i2c)
{
	int ret = stmp_reset_block(i2c->regs);
	if (ret)
		return ret;

	/*
	 * Configure timing for the I2C block. The I2C TIMING2 register has to
	 * be programmed with this particular magic number. The rest is derived
	 * from the XTAL speed and requested I2C speed.
	 *
	 * For details, see i.MX233 [25.4.2 - 25.4.4] and i.MX28 [27.5.2 - 27.5.4].
	 */
	writel(i2c->timing0, i2c->regs + MXS_I2C_TIMING0);
	writel(i2c->timing1, i2c->regs + MXS_I2C_TIMING1);
	writel(i2c->timing2, i2c->regs + MXS_I2C_TIMING2);

	writel(MXS_I2C_IRQ_MASK << 8, i2c->regs + MXS_I2C_CTRL1_SET);

	return 0;
}