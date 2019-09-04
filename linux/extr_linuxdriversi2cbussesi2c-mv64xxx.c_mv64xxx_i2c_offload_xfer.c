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
struct mv64xxx_i2c_data {int num_msgs; int block; int rc; int /*<<< orphan*/  lock; scalar_t__ reg_base; struct i2c_msg* msgs; } ;
struct i2c_msg {unsigned long addr; int flags; int len; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 unsigned long MV64XXX_I2C_BRIDGE_CONTROL_ADDR_EXT ; 
 unsigned long MV64XXX_I2C_BRIDGE_CONTROL_ADDR_SHIFT ; 
 unsigned long MV64XXX_I2C_BRIDGE_CONTROL_ENABLE ; 
 size_t MV64XXX_I2C_BRIDGE_CONTROL_RD ; 
 size_t MV64XXX_I2C_BRIDGE_CONTROL_REPEATED_START ; 
 size_t MV64XXX_I2C_BRIDGE_CONTROL_RX_SIZE_SHIFT ; 
 size_t MV64XXX_I2C_BRIDGE_CONTROL_TX_SIZE_SHIFT ; 
 size_t MV64XXX_I2C_BRIDGE_CONTROL_WR ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  mv64xxx_i2c_prepare_tx (struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  mv64xxx_i2c_wait_for_completion (struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int
mv64xxx_i2c_offload_xfer(struct mv64xxx_i2c_data *drv_data)
{
	struct i2c_msg *msgs = drv_data->msgs;
	int num = drv_data->num_msgs;
	unsigned long ctrl_reg;
	unsigned long flags;

	spin_lock_irqsave(&drv_data->lock, flags);

	/* Build transaction */
	ctrl_reg = MV64XXX_I2C_BRIDGE_CONTROL_ENABLE |
		(msgs[0].addr << MV64XXX_I2C_BRIDGE_CONTROL_ADDR_SHIFT);

	if (msgs[0].flags & I2C_M_TEN)
		ctrl_reg |= MV64XXX_I2C_BRIDGE_CONTROL_ADDR_EXT;

	/* Single write message transaction */
	if (num == 1 && !(msgs[0].flags & I2C_M_RD)) {
		size_t len = msgs[0].len - 1;

		ctrl_reg |= MV64XXX_I2C_BRIDGE_CONTROL_WR |
			(len << MV64XXX_I2C_BRIDGE_CONTROL_TX_SIZE_SHIFT);
		mv64xxx_i2c_prepare_tx(drv_data);
	}
	/* Single read message transaction */
	else if (num == 1 && msgs[0].flags & I2C_M_RD) {
		size_t len = msgs[0].len - 1;

		ctrl_reg |= MV64XXX_I2C_BRIDGE_CONTROL_RD |
			(len << MV64XXX_I2C_BRIDGE_CONTROL_RX_SIZE_SHIFT);
	}
	/*
	 * Transaction with one write and one read message. This is
	 * guaranteed by the mv64xx_i2c_can_offload() checks.
	 */
	else if (num == 2) {
		size_t lentx = msgs[0].len - 1;
		size_t lenrx = msgs[1].len - 1;

		ctrl_reg |=
			MV64XXX_I2C_BRIDGE_CONTROL_RD |
			MV64XXX_I2C_BRIDGE_CONTROL_WR |
			(lentx << MV64XXX_I2C_BRIDGE_CONTROL_TX_SIZE_SHIFT) |
			(lenrx << MV64XXX_I2C_BRIDGE_CONTROL_RX_SIZE_SHIFT) |
			MV64XXX_I2C_BRIDGE_CONTROL_REPEATED_START;
		mv64xxx_i2c_prepare_tx(drv_data);
	}

	/* Execute transaction */
	drv_data->block = 1;
	writel(ctrl_reg, drv_data->reg_base + MV64XXX_I2C_REG_BRIDGE_CONTROL);
	spin_unlock_irqrestore(&drv_data->lock, flags);

	mv64xxx_i2c_wait_for_completion(drv_data);

	return drv_data->rc;
}