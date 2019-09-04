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
struct owl_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_I2C_CTL_EN ; 
 scalar_t__ OWL_I2C_REG_CTL ; 
 scalar_t__ OWL_I2C_REG_STAT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  owl_i2c_update_reg (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void owl_i2c_reset(struct owl_i2c_dev *i2c_dev)
{
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_EN, false);
	mdelay(1);
	owl_i2c_update_reg(i2c_dev->base + OWL_I2C_REG_CTL,
			   OWL_I2C_CTL_EN, true);

	/* Clear status registers */
	writel(0, i2c_dev->base + OWL_I2C_REG_STAT);
}