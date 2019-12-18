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
struct dvb_usb_device {TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_GPIO_OUT_VAL ; 
#define  TUA9001_CMD_RESETN 129 
#define  TUA9001_CMD_RXEN 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int rtl28xxu_wr_reg_mask (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rtl2832u_tua9001_tuner_callback(struct dvb_usb_device *d,
		int cmd, int arg)
{
	int ret;
	u8 val;

	dev_dbg(&d->intf->dev, "cmd=%d arg=%d\n", cmd, arg);

	/*
	 * CEN     always enabled by hardware wiring
	 * RESETN  GPIO4
	 * RXEN    GPIO1
	 */

	switch (cmd) {
	case TUA9001_CMD_RESETN:
		if (arg)
			val = (1 << 4);
		else
			val = (0 << 4);

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, val, 0x10);
		if (ret)
			goto err;
		break;
	case TUA9001_CMD_RXEN:
		if (arg)
			val = (1 << 1);
		else
			val = (0 << 1);

		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, val, 0x02);
		if (ret)
			goto err;
		break;
	}

	return 0;
err:
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}