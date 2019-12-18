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
 int EINVAL ; 
#define  FC_FE_CALLBACK_VHF_ENABLE 128 
 int /*<<< orphan*/  SYS_GPIO_OUT_VAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int rtl28xxu_rd_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int rtl28xxu_wr_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl2832u_fc0012_tuner_callback(struct dvb_usb_device *d,
		int cmd, int arg)
{
	int ret;
	u8 val;

	dev_dbg(&d->intf->dev, "cmd=%d arg=%d\n", cmd, arg);

	switch (cmd) {
	case FC_FE_CALLBACK_VHF_ENABLE:
		/* set output values */
		ret = rtl28xxu_rd_reg(d, SYS_GPIO_OUT_VAL, &val);
		if (ret)
			goto err;

		if (arg)
			val &= 0xbf; /* set GPIO6 low */
		else
			val |= 0x40; /* set GPIO6 high */


		ret = rtl28xxu_wr_reg(d, SYS_GPIO_OUT_VAL, val);
		if (ret)
			goto err;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}
	return 0;
err:
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}