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
typedef  int u8 ;
struct i2c_msg {int len; int addr; int /*<<< orphan*/  buf; } ;
struct friio_priv {TYPE_1__* i2c_client_demod; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GL861_REQ_I2C_RAW ; 
 int /*<<< orphan*/  GL861_WRITE ; 
 struct friio_priv* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
friio_i2c_tuner_write(struct dvb_usb_device *d, struct i2c_msg *msg)
{
	u8 *buf;
	int ret;
	struct friio_priv *priv;

	priv = d_to_priv(d);

	if (msg->len < 1)
		return -EINVAL;

	buf = kmalloc(msg->len + 1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	buf[0] = msg->addr << 1;
	memcpy(buf + 1, msg->buf, msg->len);

	ret = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev, 0),
				 GL861_REQ_I2C_RAW, GL861_WRITE,
				 priv->i2c_client_demod->addr << (8 + 1),
				 0xFE, buf, msg->len + 1, 2000);
	kfree(buf);
	return ret;
}