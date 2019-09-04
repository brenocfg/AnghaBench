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
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int zd1301_ctrl_msg (struct dvb_usb_device*,int*,int,int*,int) ; 

__attribute__((used)) static int zd1301_demod_rreg(void *reg_priv, u16 reg, u8 *val)
{
	struct dvb_usb_device *d = reg_priv;
	struct usb_interface *intf = d->intf;
	int ret;
	u8 buf[7] = {0x07, 0x00, 0x04, 0x01,
		     (reg >> 0) & 0xff, (reg >> 8) & 0xff, 0};

	ret = zd1301_ctrl_msg(d, buf, 7, buf, 7);
	if (ret)
		goto err;

	*val = buf[6];

	return 0;
err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);
	return ret;
}