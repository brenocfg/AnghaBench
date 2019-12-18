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
struct mxs_i2c_dev {int cmd_err; scalar_t__ regs; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 scalar_t__ MXS_I2C_CTRL1_CLR ; 
 int MXS_I2C_CTRL1_EARLY_TERM_IRQ ; 
 int MXS_I2C_CTRL1_MASTER_LOSS_IRQ ; 
 int MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ ; 
 int MXS_I2C_CTRL1_SLAVE_IRQ ; 
 int MXS_I2C_CTRL1_SLAVE_STOP_IRQ ; 
 int MXS_I2C_IRQ_MASK ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int mxs_i2c_pio_check_error_state(struct mxs_i2c_dev *i2c)
{
	u32 state;

	state = readl(i2c->regs + MXS_I2C_CTRL1_CLR) & MXS_I2C_IRQ_MASK;

	if (state & MXS_I2C_CTRL1_NO_SLAVE_ACK_IRQ)
		i2c->cmd_err = -ENXIO;
	else if (state & (MXS_I2C_CTRL1_EARLY_TERM_IRQ |
			  MXS_I2C_CTRL1_MASTER_LOSS_IRQ |
			  MXS_I2C_CTRL1_SLAVE_STOP_IRQ |
			  MXS_I2C_CTRL1_SLAVE_IRQ))
		i2c->cmd_err = -EIO;

	return i2c->cmd_err;
}