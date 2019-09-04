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
struct mv64xxx_i2c_data {int num_msgs; int /*<<< orphan*/  waitq; scalar_t__ block; scalar_t__ reg_base; TYPE_1__* msgs; int /*<<< orphan*/  rc; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int I2C_M_RD ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int MV64XXX_I2C_BRIDGE_STATUS_ERROR ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_CONTROL ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_STATUS ; 
 int /*<<< orphan*/  mv64xxx_i2c_read_offload_rx_data (struct mv64xxx_i2c_data*,TYPE_1__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
mv64xxx_i2c_intr_offload(struct mv64xxx_i2c_data *drv_data)
{
	u32 cause, status;

	cause = readl(drv_data->reg_base +
		      MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE);
	if (!cause)
		return IRQ_NONE;

	status = readl(drv_data->reg_base +
		       MV64XXX_I2C_REG_BRIDGE_STATUS);

	if (status & MV64XXX_I2C_BRIDGE_STATUS_ERROR) {
		drv_data->rc = -EIO;
		goto out;
	}

	drv_data->rc = 0;

	/*
	 * Transaction is a one message read transaction, read data
	 * for this message.
	 */
	if (drv_data->num_msgs == 1 && drv_data->msgs[0].flags & I2C_M_RD) {
		mv64xxx_i2c_read_offload_rx_data(drv_data, drv_data->msgs);
		drv_data->msgs++;
		drv_data->num_msgs--;
	}
	/*
	 * Transaction is a two messages write/read transaction, read
	 * data for the second (read) message.
	 */
	else if (drv_data->num_msgs == 2 &&
		 !(drv_data->msgs[0].flags & I2C_M_RD) &&
		 drv_data->msgs[1].flags & I2C_M_RD) {
		mv64xxx_i2c_read_offload_rx_data(drv_data, drv_data->msgs + 1);
		drv_data->msgs += 2;
		drv_data->num_msgs -= 2;
	}

out:
	writel(0, drv_data->reg_base +	MV64XXX_I2C_REG_BRIDGE_CONTROL);
	writel(0, drv_data->reg_base +
	       MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE);
	drv_data->block = 0;

	wake_up(&drv_data->waitq);

	return IRQ_HANDLED;
}