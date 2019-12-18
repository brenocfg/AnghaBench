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
typedef  int u8 ;
struct i2c_msg {int addr; int flags; int len; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; TYPE_2__* udev; } ;
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  ibuf ;
struct TYPE_3__ {int /*<<< orphan*/  idVendor; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_I2C_READ ; 
 int /*<<< orphan*/  CMD_I2C_WRITE ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int EREMOTEIO ; 
 int I2C_M_RD ; 
 int MAX_XFER_SIZE ; 
 scalar_t__ USB_VID_MEDION ; 
 scalar_t__ cxusb_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*,int,int*,int) ; 
 int /*<<< orphan*/  cxusb_gpio_tuner (struct dvb_usb_device*,int) ; 
 int /*<<< orphan*/  deb_i2c (char*) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int cxusb_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
			  int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int ret;
	int i;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		if (le16_to_cpu(d->udev->descriptor.idVendor) == USB_VID_MEDION)
			switch (msg[i].addr) {
			case 0x63:
				cxusb_gpio_tuner(d, 0);
				break;
			default:
				cxusb_gpio_tuner(d, 1);
				break;
			}

		if (msg[i].flags & I2C_M_RD) {
			/* read only */
			u8 obuf[3], ibuf[MAX_XFER_SIZE];

			if (1 + msg[i].len > sizeof(ibuf)) {
				warn("i2c rd: len=%d is too big!\n",
				     msg[i].len);
				ret = -EOPNOTSUPP;
				goto unlock;
			}
			obuf[0] = 0;
			obuf[1] = msg[i].len;
			obuf[2] = msg[i].addr;
			if (cxusb_ctrl_msg(d, CMD_I2C_READ,
					   obuf, 3,
					   ibuf, 1 + msg[i].len) < 0) {
				warn("i2c read failed");
				break;
			}
			memcpy(msg[i].buf, &ibuf[1], msg[i].len);
		} else if (i + 1 < num && (msg[i + 1].flags & I2C_M_RD) &&
			   msg[i].addr == msg[i + 1].addr) {
			/* write to then read from same address */
			u8 obuf[MAX_XFER_SIZE], ibuf[MAX_XFER_SIZE];

			if (3 + msg[i].len > sizeof(obuf)) {
				warn("i2c wr: len=%d is too big!\n",
				     msg[i].len);
				ret = -EOPNOTSUPP;
				goto unlock;
			}
			if (1 + msg[i + 1].len > sizeof(ibuf)) {
				warn("i2c rd: len=%d is too big!\n",
				     msg[i + 1].len);
				ret = -EOPNOTSUPP;
				goto unlock;
			}
			obuf[0] = msg[i].len;
			obuf[1] = msg[i + 1].len;
			obuf[2] = msg[i].addr;
			memcpy(&obuf[3], msg[i].buf, msg[i].len);

			if (cxusb_ctrl_msg(d, CMD_I2C_READ,
					   obuf, 3 + msg[i].len,
					   ibuf, 1 + msg[i + 1].len) < 0)
				break;

			if (ibuf[0] != 0x08)
				deb_i2c("i2c read may have failed\n");

			memcpy(msg[i + 1].buf, &ibuf[1], msg[i + 1].len);

			i++;
		} else {
			/* write only */
			u8 obuf[MAX_XFER_SIZE], ibuf;

			if (2 + msg[i].len > sizeof(obuf)) {
				warn("i2c wr: len=%d is too big!\n",
				     msg[i].len);
				ret = -EOPNOTSUPP;
				goto unlock;
			}
			obuf[0] = msg[i].addr;
			obuf[1] = msg[i].len;
			memcpy(&obuf[2], msg[i].buf, msg[i].len);

			if (cxusb_ctrl_msg(d, CMD_I2C_WRITE, obuf,
					   2 + msg[i].len, &ibuf, 1) < 0)
				break;
			if (ibuf != 0x08)
				deb_i2c("i2c write may have failed\n");
		}
	}

	if (i == num)
		ret = num;
	else
		ret = -EREMOTEIO;

unlock:
	mutex_unlock(&d->i2c_mutex);
	return ret;
}