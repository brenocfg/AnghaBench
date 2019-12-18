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
struct i2c_msg {int flags; } ;
struct efm32_i2c_ddata {size_t current_msg; int /*<<< orphan*/  done; int /*<<< orphan*/  retval; struct i2c_msg* msgs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENXIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_CMD ; 
 int REG_CMD_ABORT ; 
 int REG_CMD_CLEARPC ; 
 int REG_CMD_CLEARTX ; 
 int REG_CMD_STOP ; 
 int /*<<< orphan*/  REG_IF ; 
 int /*<<< orphan*/  REG_IFC ; 
 int REG_IFC__MASK ; 
 int /*<<< orphan*/  REG_STATE ; 
 int REG_STATE_NACKED ; 
#define  REG_STATE_STATE_ADDR 134 
#define  REG_STATE_STATE_ADDRACK 133 
#define  REG_STATE_STATE_DATA 132 
#define  REG_STATE_STATE_DATAACK 131 
#define  REG_STATE_STATE_IDLE 130 
#define  REG_STATE_STATE_START 129 
#define  REG_STATE_STATE_WAIT 128 
 int REG_STATE_STATE__MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int efm32_i2c_read32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efm32_i2c_recv_next_byte (struct efm32_i2c_ddata*) ; 
 int /*<<< orphan*/  efm32_i2c_send_next_byte (struct efm32_i2c_ddata*) ; 
 int /*<<< orphan*/  efm32_i2c_write32 (struct efm32_i2c_ddata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t efm32_i2c_irq(int irq, void *dev_id)
{
	struct efm32_i2c_ddata *ddata = dev_id;
	struct i2c_msg *cur_msg = &ddata->msgs[ddata->current_msg];
	u32 irqflag = efm32_i2c_read32(ddata, REG_IF);
	u32 state = efm32_i2c_read32(ddata, REG_STATE);

	efm32_i2c_write32(ddata, REG_IFC, irqflag & REG_IFC__MASK);

	switch (state & REG_STATE_STATE__MASK) {
	case REG_STATE_STATE_IDLE:
		/* arbitration lost? */
		ddata->retval = -EAGAIN;
		complete(&ddata->done);
		break;
	case REG_STATE_STATE_WAIT:
		/*
		 * huh, this shouldn't happen.
		 * Reset hardware state and get out
		 */
		ddata->retval = -EIO;
		efm32_i2c_write32(ddata, REG_CMD,
				REG_CMD_STOP | REG_CMD_ABORT |
				REG_CMD_CLEARTX | REG_CMD_CLEARPC);
		complete(&ddata->done);
		break;
	case REG_STATE_STATE_START:
		/* "caller" is expected to send an address */
		break;
	case REG_STATE_STATE_ADDR:
		/* wait for Ack or NAck of slave */
		break;
	case REG_STATE_STATE_ADDRACK:
		if (state & REG_STATE_NACKED) {
			efm32_i2c_write32(ddata, REG_CMD, REG_CMD_STOP);
			ddata->retval = -ENXIO;
			complete(&ddata->done);
		} else if (cur_msg->flags & I2C_M_RD) {
			/* wait for slave to send first data byte */
		} else {
			efm32_i2c_send_next_byte(ddata);
		}
		break;
	case REG_STATE_STATE_DATA:
		if (cur_msg->flags & I2C_M_RD) {
			efm32_i2c_recv_next_byte(ddata);
		} else {
			/* wait for Ack or Nack of slave */
		}
		break;
	case REG_STATE_STATE_DATAACK:
		if (state & REG_STATE_NACKED) {
			efm32_i2c_write32(ddata, REG_CMD, REG_CMD_STOP);
			complete(&ddata->done);
		} else {
			efm32_i2c_send_next_byte(ddata);
		}
	}

	return IRQ_HANDLED;
}