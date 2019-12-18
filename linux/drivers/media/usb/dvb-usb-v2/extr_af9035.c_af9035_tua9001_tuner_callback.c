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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;

/* Variables and functions */
#define  TUA9001_CMD_RESETN 129 
#define  TUA9001_CMD_RXEN 128 
 int af9035_wr_reg_mask (struct dvb_usb_device*,int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 

__attribute__((used)) static int af9035_tua9001_tuner_callback(struct dvb_usb_device *d,
		int cmd, int arg)
{
	struct usb_interface *intf = d->intf;
	int ret;
	u8 val;

	dev_dbg(&intf->dev, "cmd=%d arg=%d\n", cmd, arg);

	/*
	 * CEN     always enabled by hardware wiring
	 * RESETN  GPIOT3
	 * RXEN    GPIOT2
	 */

	switch (cmd) {
	case TUA9001_CMD_RESETN:
		if (arg)
			val = 0x00;
		else
			val = 0x01;

		ret = af9035_wr_reg_mask(d, 0x00d8e7, val, 0x01);
		if (ret < 0)
			goto err;
		break;
	case TUA9001_CMD_RXEN:
		if (arg)
			val = 0x01;
		else
			val = 0x00;

		ret = af9035_wr_reg_mask(d, 0x00d8eb, val, 0x01);
		if (ret < 0)
			goto err;
		break;
	}

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}