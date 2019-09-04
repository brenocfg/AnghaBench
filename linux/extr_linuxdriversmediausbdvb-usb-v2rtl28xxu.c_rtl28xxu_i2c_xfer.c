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
struct rtl28xxu_req {int value; int index; int size; int* data; } ;
struct rtl28xxu_dev {int page; int /*<<< orphan*/  new_i2c_write; } ;
struct i2c_msg {int flags; int len; int addr; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; struct rtl28xxu_dev* priv; } ;

/* Variables and functions */
 int CMD_DEMOD_RD ; 
 int CMD_DEMOD_WR ; 
 void* CMD_I2C_DA_RD ; 
 void* CMD_I2C_DA_WR ; 
 int CMD_I2C_RD ; 
 int CMD_I2C_WR ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int EPIPE ; 
 int I2C_M_RD ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtl28xxu_ctrl_msg (struct dvb_usb_device*,struct rtl28xxu_req*) ; 

__attribute__((used)) static int rtl28xxu_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
	int num)
{
	int ret;
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct rtl28xxu_dev *dev = d->priv;
	struct rtl28xxu_req req;

	/*
	 * It is not known which are real I2C bus xfer limits, but testing
	 * with RTL2831U + MT2060 gives max RD 24 and max WR 22 bytes.
	 * TODO: find out RTL2832U lens
	 */

	/*
	 * I2C adapter logic looks rather complicated due to fact it handles
	 * three different access methods. Those methods are;
	 * 1) integrated demod access
	 * 2) old I2C access
	 * 3) new I2C access
	 *
	 * Used method is selected in order 1, 2, 3. Method 3 can handle all
	 * requests but there is two reasons why not use it always;
	 * 1) It is most expensive, usually two USB messages are needed
	 * 2) At least RTL2831U does not support it
	 *
	 * Method 3 is needed in case of I2C write+read (typical register read)
	 * where write is more than one byte.
	 */

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	if (num == 2 && !(msg[0].flags & I2C_M_RD) &&
		(msg[1].flags & I2C_M_RD)) {
		if (msg[0].len > 24 || msg[1].len > 24) {
			/* TODO: check msg[0].len max */
			ret = -EOPNOTSUPP;
			goto err_mutex_unlock;
		} else if (msg[0].addr == 0x10) {
			/* method 1 - integrated demod */
			if (msg[0].buf[0] == 0x00) {
				/* return demod page from driver cache */
				msg[1].buf[0] = dev->page;
				ret = 0;
			} else {
				req.value = (msg[0].buf[0] << 8) | (msg[0].addr << 1);
				req.index = CMD_DEMOD_RD | dev->page;
				req.size = msg[1].len;
				req.data = &msg[1].buf[0];
				ret = rtl28xxu_ctrl_msg(d, &req);
			}
		} else if (msg[0].len < 2) {
			/* method 2 - old I2C */
			req.value = (msg[0].buf[0] << 8) | (msg[0].addr << 1);
			req.index = CMD_I2C_RD;
			req.size = msg[1].len;
			req.data = &msg[1].buf[0];
			ret = rtl28xxu_ctrl_msg(d, &req);
		} else {
			/* method 3 - new I2C */
			req.value = (msg[0].addr << 1);
			req.index = CMD_I2C_DA_WR;
			req.size = msg[0].len;
			req.data = msg[0].buf;
			ret = rtl28xxu_ctrl_msg(d, &req);
			if (ret)
				goto err_mutex_unlock;

			req.value = (msg[0].addr << 1);
			req.index = CMD_I2C_DA_RD;
			req.size = msg[1].len;
			req.data = msg[1].buf;
			ret = rtl28xxu_ctrl_msg(d, &req);
		}
	} else if (num == 1 && !(msg[0].flags & I2C_M_RD)) {
		if (msg[0].len > 22) {
			/* TODO: check msg[0].len max */
			ret = -EOPNOTSUPP;
			goto err_mutex_unlock;
		} else if (msg[0].addr == 0x10) {
			/* method 1 - integrated demod */
			if (msg[0].buf[0] == 0x00) {
				/* save demod page for later demod access */
				dev->page = msg[0].buf[1];
				ret = 0;
			} else {
				req.value = (msg[0].buf[0] << 8) |
					(msg[0].addr << 1);
				req.index = CMD_DEMOD_WR | dev->page;
				req.size = msg[0].len-1;
				req.data = &msg[0].buf[1];
				ret = rtl28xxu_ctrl_msg(d, &req);
			}
		} else if ((msg[0].len < 23) && (!dev->new_i2c_write)) {
			/* method 2 - old I2C */
			req.value = (msg[0].buf[0] << 8) | (msg[0].addr << 1);
			req.index = CMD_I2C_WR;
			req.size = msg[0].len-1;
			req.data = &msg[0].buf[1];
			ret = rtl28xxu_ctrl_msg(d, &req);
		} else {
			/* method 3 - new I2C */
			req.value = (msg[0].addr << 1);
			req.index = CMD_I2C_DA_WR;
			req.size = msg[0].len;
			req.data = msg[0].buf;
			ret = rtl28xxu_ctrl_msg(d, &req);
		}
	} else if (num == 1 && (msg[0].flags & I2C_M_RD)) {
		req.value = (msg[0].addr << 1);
		req.index = CMD_I2C_DA_RD;
		req.size = msg[0].len;
		req.data = msg[0].buf;
		ret = rtl28xxu_ctrl_msg(d, &req);
	} else {
		ret = -EOPNOTSUPP;
	}

	/* Retry failed I2C messages */
	if (ret == -EPIPE)
		ret = -EAGAIN;

err_mutex_unlock:
	mutex_unlock(&d->i2c_mutex);

	return ret ? ret : num;
}