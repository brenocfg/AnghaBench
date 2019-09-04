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
typedef  int u8 ;
struct kempld_i2c_data {scalar_t__ state; int pos; scalar_t__ nmsgs; struct i2c_msg* msg; struct kempld_device_data* pld; } ;
struct kempld_device_data {int dummy; } ;
struct i2c_msg {int flags; int addr; int* buf; int len; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int I2C_CMD_IACK ; 
 int I2C_CMD_READ_ACK ; 
 int I2C_CMD_READ_NACK ; 
 int I2C_CMD_START ; 
 int I2C_CMD_STOP ; 
 int I2C_CMD_WRITE ; 
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int I2C_STAT_ARBLOST ; 
 int I2C_STAT_BUSY ; 
 int I2C_STAT_NACK ; 
 int I2C_STAT_TIP ; 
 int /*<<< orphan*/  KEMPLD_I2C_CMD ; 
 int /*<<< orphan*/  KEMPLD_I2C_DATA ; 
 int /*<<< orphan*/  KEMPLD_I2C_STAT ; 
 scalar_t__ STATE_ADDR ; 
 scalar_t__ STATE_ADDR10 ; 
 scalar_t__ STATE_DONE ; 
 scalar_t__ STATE_ERROR ; 
 scalar_t__ STATE_INIT ; 
 scalar_t__ STATE_READ ; 
 scalar_t__ STATE_START ; 
 scalar_t__ STATE_WRITE ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 void* kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_write8 (struct kempld_device_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kempld_i2c_process(struct kempld_i2c_data *i2c)
{
	struct kempld_device_data *pld = i2c->pld;
	u8 stat = kempld_read8(pld, KEMPLD_I2C_STAT);
	struct i2c_msg *msg = i2c->msg;
	u8 addr;

	/* Ready? */
	if (stat & I2C_STAT_TIP)
		return -EBUSY;

	if (i2c->state == STATE_DONE || i2c->state == STATE_ERROR) {
		/* Stop has been sent */
		kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_IACK);
		if (i2c->state == STATE_ERROR)
			return -EIO;
		return 0;
	}

	/* Error? */
	if (stat & I2C_STAT_ARBLOST) {
		i2c->state = STATE_ERROR;
		kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
		return -EAGAIN;
	}

	if (i2c->state == STATE_INIT) {
		if (stat & I2C_STAT_BUSY)
			return -EBUSY;

		i2c->state = STATE_ADDR;
	}

	if (i2c->state == STATE_ADDR) {
		/* 10 bit address? */
		if (i2c->msg->flags & I2C_M_TEN) {
			addr = 0xf0 | ((i2c->msg->addr >> 7) & 0x6);
			/* Set read bit if necessary */
			addr |= (i2c->msg->flags & I2C_M_RD) ? 1 : 0;
			i2c->state = STATE_ADDR10;
		} else {
			addr = i2c_8bit_addr_from_msg(i2c->msg);
			i2c->state = STATE_START;
		}

		kempld_write8(pld, KEMPLD_I2C_DATA, addr);
		kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_START);

		return 0;
	}

	/* Second part of 10 bit addressing */
	if (i2c->state == STATE_ADDR10) {
		kempld_write8(pld, KEMPLD_I2C_DATA, i2c->msg->addr & 0xff);
		kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_WRITE);

		i2c->state = STATE_START;
		return 0;
	}

	if (i2c->state == STATE_START || i2c->state == STATE_WRITE) {
		i2c->state = (msg->flags & I2C_M_RD) ? STATE_READ : STATE_WRITE;

		if (stat & I2C_STAT_NACK) {
			i2c->state = STATE_ERROR;
			kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
			return -ENXIO;
		}
	} else {
		msg->buf[i2c->pos++] = kempld_read8(pld, KEMPLD_I2C_DATA);
	}

	if (i2c->pos >= msg->len) {
		i2c->nmsgs--;
		i2c->msg++;
		i2c->pos = 0;
		msg = i2c->msg;

		if (i2c->nmsgs) {
			if (!(msg->flags & I2C_M_NOSTART)) {
				i2c->state = STATE_ADDR;
				return 0;
			} else {
				i2c->state = (msg->flags & I2C_M_RD)
					? STATE_READ : STATE_WRITE;
			}
		} else {
			i2c->state = STATE_DONE;
			kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
			return 0;
		}
	}

	if (i2c->state == STATE_READ) {
		kempld_write8(pld, KEMPLD_I2C_CMD, i2c->pos == (msg->len - 1) ?
			      I2C_CMD_READ_NACK : I2C_CMD_READ_ACK);
	} else {
		kempld_write8(pld, KEMPLD_I2C_DATA, msg->buf[i2c->pos++]);
		kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_WRITE);
	}

	return 0;
}