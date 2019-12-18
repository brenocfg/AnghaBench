#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_msg {int flags; scalar_t__ addr; scalar_t__* buf; scalar_t__ len; } ;
struct i2c_adapter {int dummy; } ;
struct ec168_req {scalar_t__ value; scalar_t__ index; scalar_t__* data; scalar_t__ size; int /*<<< orphan*/  cmd; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; TYPE_1__* udev; } ;
struct TYPE_4__ {scalar_t__ demod_address; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  READ_DEMOD ; 
 int /*<<< orphan*/  WRITE_DEMOD ; 
 int /*<<< orphan*/  WRITE_I2C ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ec168_ctrl_msg (struct dvb_usb_device*,struct ec168_req*) ; 
 TYPE_2__ ec168_ec100_config ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec168_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
	int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct ec168_req req;
	int i = 0;
	int ret;

	if (num > 2)
		return -EINVAL;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	while (i < num) {
		if (num > i + 1 && (msg[i+1].flags & I2C_M_RD)) {
			if (msg[i].addr == ec168_ec100_config.demod_address) {
				req.cmd = READ_DEMOD;
				req.value = 0;
				req.index = 0xff00 + msg[i].buf[0]; /* reg */
				req.size = msg[i+1].len; /* bytes to read */
				req.data = &msg[i+1].buf[0];
				ret = ec168_ctrl_msg(d, &req);
				i += 2;
			} else {
				dev_err(&d->udev->dev, "%s: I2C read not " \
						"implemented\n",
						KBUILD_MODNAME);
				ret = -EOPNOTSUPP;
				i += 2;
			}
		} else {
			if (msg[i].addr == ec168_ec100_config.demod_address) {
				req.cmd = WRITE_DEMOD;
				req.value = msg[i].buf[1]; /* val */
				req.index = 0xff00 + msg[i].buf[0]; /* reg */
				req.size = 0;
				req.data = NULL;
				ret = ec168_ctrl_msg(d, &req);
				i += 1;
			} else {
				req.cmd = WRITE_I2C;
				req.value = msg[i].buf[0]; /* val */
				req.index = 0x0100 + msg[i].addr; /* I2C addr */
				req.size = msg[i].len-1;
				req.data = &msg[i].buf[1];
				ret = ec168_ctrl_msg(d, &req);
				i += 1;
			}
		}
		if (ret)
			goto error;

	}
	ret = i;

error:
	mutex_unlock(&d->i2c_mutex);
	return ret;
}