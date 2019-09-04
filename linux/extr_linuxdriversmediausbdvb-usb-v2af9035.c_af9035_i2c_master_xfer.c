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
typedef  int u32 ;
struct usb_req {int member_2; int* member_3; int member_4; int* member_5; int wlen; int mbox; void* cmd; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct state {scalar_t__* af9033_i2c_addr; int chip_type; scalar_t__ no_read; } ;
struct i2c_msg {int flags; int len; scalar_t__ addr; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* CMD_GENERIC_I2C_RD ; 
 void* CMD_GENERIC_I2C_WR ; 
 int /*<<< orphan*/  CMD_I2C_RD ; 
 int /*<<< orphan*/  CMD_I2C_WR ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int I2C_M_RD ; 
 int MAX_XFER_SIZE ; 
 int af9035_ctrl_msg (struct dvb_usb_device*,struct usb_req*) ; 
 int af9035_rd_regs (struct dvb_usb_device*,int,int*,int) ; 
 int af9035_wr_regs (struct dvb_usb_device*,int,int*,int) ; 
 struct state* d_to_priv (struct dvb_usb_device*) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int af9035_i2c_master_xfer(struct i2c_adapter *adap,
		struct i2c_msg msg[], int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct state *state = d_to_priv(d);
	int ret;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	/*
	 * AF9035 I2C sub header is 5 bytes long. Meaning of those bytes are:
	 * 0: data len
	 * 1: I2C addr << 1
	 * 2: reg addr len
	 *    byte 3 and 4 can be used as reg addr
	 * 3: reg addr MSB
	 *    used when reg addr len is set to 2
	 * 4: reg addr LSB
	 *    used when reg addr len is set to 1 or 2
	 *
	 * For the simplify we do not use register addr at all.
	 * NOTE: As a firmware knows tuner type there is very small possibility
	 * there could be some tuner I2C hacks done by firmware and this may
	 * lead problems if firmware expects those bytes are used.
	 *
	 * TODO: Here is few hacks. AF9035 chip integrates AF9033 demodulator.
	 * IT9135 chip integrates AF9033 demodulator and RF tuner. For dual
	 * tuner devices, there is also external AF9033 demodulator connected
	 * via external I2C bus. All AF9033 demod I2C traffic, both single and
	 * dual tuner configuration, is covered by firmware - actual USB IO
	 * looks just like a memory access.
	 * In case of IT913x chip, there is own tuner driver. It is implemented
	 * currently as a I2C driver, even tuner IP block is likely build
	 * directly into the demodulator memory space and there is no own I2C
	 * bus. I2C subsystem does not allow register multiple devices to same
	 * bus, having same slave address. Due to that we reuse demod address,
	 * shifted by one bit, on that case.
	 *
	 * For IT930x we use a different command and the sub header is
	 * different as well:
	 * 0: data len
	 * 1: I2C bus (0x03 seems to be only value used)
	 * 2: I2C addr << 1
	 */
#define AF9035_IS_I2C_XFER_WRITE_READ(_msg, _num) \
	(_num == 2 && !(_msg[0].flags & I2C_M_RD) && (_msg[1].flags & I2C_M_RD))
#define AF9035_IS_I2C_XFER_WRITE(_msg, _num) \
	(_num == 1 && !(_msg[0].flags & I2C_M_RD))
#define AF9035_IS_I2C_XFER_READ(_msg, _num) \
	(_num == 1 && (_msg[0].flags & I2C_M_RD))

	if (AF9035_IS_I2C_XFER_WRITE_READ(msg, num)) {
		if (msg[0].len > 40 || msg[1].len > 40) {
			/* TODO: correct limits > 40 */
			ret = -EOPNOTSUPP;
		} else if ((msg[0].addr == state->af9033_i2c_addr[0]) ||
			   (msg[0].addr == state->af9033_i2c_addr[1])) {
			/* demod access via firmware interface */
			u32 reg = msg[0].buf[0] << 16 | msg[0].buf[1] << 8 |
					msg[0].buf[2];

			if (msg[0].addr == state->af9033_i2c_addr[1])
				reg |= 0x100000;

			ret = af9035_rd_regs(d, reg, &msg[1].buf[0],
					msg[1].len);
		} else if (state->no_read) {
			memset(msg[1].buf, 0, msg[1].len);
			ret = 0;
		} else {
			/* I2C write + read */
			u8 buf[MAX_XFER_SIZE];
			struct usb_req req = { CMD_I2C_RD, 0, 5 + msg[0].len,
					buf, msg[1].len, msg[1].buf };

			if (state->chip_type == 0x9306) {
				req.cmd = CMD_GENERIC_I2C_RD;
				req.wlen = 3 + msg[0].len;
			}
			req.mbox |= ((msg[0].addr & 0x80)  >>  3);

			buf[0] = msg[1].len;
			if (state->chip_type == 0x9306) {
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addr << 1;
				memcpy(&buf[3], msg[0].buf, msg[0].len);
			} else {
				buf[1] = msg[0].addr << 1;
				buf[3] = 0x00; /* reg addr MSB */
				buf[4] = 0x00; /* reg addr LSB */

				/* Keep prev behavior for write req len > 2*/
				if (msg[0].len > 2) {
					buf[2] = 0x00; /* reg addr len */
					memcpy(&buf[5], msg[0].buf, msg[0].len);

				/* Use reg addr fields if write req len <= 2 */
				} else {
					req.wlen = 5;
					buf[2] = msg[0].len;
					if (msg[0].len == 2) {
						buf[3] = msg[0].buf[0];
						buf[4] = msg[0].buf[1];
					} else if (msg[0].len == 1) {
						buf[4] = msg[0].buf[0];
					}
				}
			}
			ret = af9035_ctrl_msg(d, &req);
		}
	} else if (AF9035_IS_I2C_XFER_WRITE(msg, num)) {
		if (msg[0].len > 40) {
			/* TODO: correct limits > 40 */
			ret = -EOPNOTSUPP;
		} else if ((msg[0].addr == state->af9033_i2c_addr[0]) ||
			   (msg[0].addr == state->af9033_i2c_addr[1])) {
			/* demod access via firmware interface */
			u32 reg = msg[0].buf[0] << 16 | msg[0].buf[1] << 8 |
					msg[0].buf[2];

			if (msg[0].addr == state->af9033_i2c_addr[1])
				reg |= 0x100000;

			ret = (msg[0].len >= 3) ? af9035_wr_regs(d, reg,
							         &msg[0].buf[3],
							         msg[0].len - 3)
					        : -EOPNOTSUPP;
		} else {
			/* I2C write */
			u8 buf[MAX_XFER_SIZE];
			struct usb_req req = { CMD_I2C_WR, 0, 5 + msg[0].len,
					buf, 0, NULL };

			if (state->chip_type == 0x9306) {
				req.cmd = CMD_GENERIC_I2C_WR;
				req.wlen = 3 + msg[0].len;
			}

			req.mbox |= ((msg[0].addr & 0x80)  >>  3);
			buf[0] = msg[0].len;
			if (state->chip_type == 0x9306) {
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addr << 1;
				memcpy(&buf[3], msg[0].buf, msg[0].len);
			} else {
				buf[1] = msg[0].addr << 1;
				buf[2] = 0x00; /* reg addr len */
				buf[3] = 0x00; /* reg addr MSB */
				buf[4] = 0x00; /* reg addr LSB */
				memcpy(&buf[5], msg[0].buf, msg[0].len);
			}
			ret = af9035_ctrl_msg(d, &req);
		}
	} else if (AF9035_IS_I2C_XFER_READ(msg, num)) {
		if (msg[0].len > 40) {
			/* TODO: correct limits > 40 */
			ret = -EOPNOTSUPP;
		} else if (state->no_read) {
			memset(msg[0].buf, 0, msg[0].len);
			ret = 0;
		} else {
			/* I2C read */
			u8 buf[5];
			struct usb_req req = { CMD_I2C_RD, 0, sizeof(buf),
						buf, msg[0].len, msg[0].buf };

			if (state->chip_type == 0x9306) {
				req.cmd = CMD_GENERIC_I2C_RD;
				req.wlen = 3;
			}
			req.mbox |= ((msg[0].addr & 0x80)  >>  3);
			buf[0] = msg[0].len;
			if (state->chip_type == 0x9306) {
				buf[1] = 0x03; /* I2C bus */
				buf[2] = msg[0].addr << 1;
			} else {
				buf[1] = msg[0].addr << 1;
				buf[2] = 0x00; /* reg addr len */
				buf[3] = 0x00; /* reg addr MSB */
				buf[4] = 0x00; /* reg addr LSB */
			}
			ret = af9035_ctrl_msg(d, &req);
		}
	} else {
		/*
		 * We support only three kind of I2C transactions:
		 * 1) 1 x write + 1 x read (repeated start)
		 * 2) 1 x write
		 * 3) 1 x read
		 */
		ret = -EOPNOTSUPP;
	}

	mutex_unlock(&d->i2c_mutex);

	if (ret < 0)
		return ret;
	else
		return num;
}