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
struct dvb_usb_device {TYPE_1__* intf; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_GPIO_OUT_VAL ; 
 int /*<<< orphan*/  SYS_SYS0 ; 
 int /*<<< orphan*/  USB_EPA_CTL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int rtl28xxu_rd_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int rtl28xxu_wr_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 
 int rtl28xxu_wr_regs (struct dvb_usb_device*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl2831u_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	int ret;
	u8 gpio, sys0, epa_ctl[2];

	dev_dbg(&d->intf->dev, "onoff=%d\n", onoff);

	/* demod adc */
	ret = rtl28xxu_rd_reg(d, SYS_SYS0, &sys0);
	if (ret)
		goto err;

	/* tuner power, read GPIOs */
	ret = rtl28xxu_rd_reg(d, SYS_GPIO_OUT_VAL, &gpio);
	if (ret)
		goto err;

	dev_dbg(&d->intf->dev, "RD SYS0=%02x GPIO_OUT_VAL=%02x\n", sys0, gpio);

	if (onoff) {
		gpio |= 0x01; /* GPIO0 = 1 */
		gpio &= (~0x10); /* GPIO4 = 0 */
		gpio |= 0x04; /* GPIO2 = 1, LED on */
		sys0 = sys0 & 0x0f;
		sys0 |= 0xe0;
		epa_ctl[0] = 0x00; /* clear stall */
		epa_ctl[1] = 0x00; /* clear reset */
	} else {
		gpio &= (~0x01); /* GPIO0 = 0 */
		gpio |= 0x10; /* GPIO4 = 1 */
		gpio &= (~0x04); /* GPIO2 = 1, LED off */
		sys0 = sys0 & (~0xc0);
		epa_ctl[0] = 0x10; /* set stall */
		epa_ctl[1] = 0x02; /* set reset */
	}

	dev_dbg(&d->intf->dev, "WR SYS0=%02x GPIO_OUT_VAL=%02x\n", sys0, gpio);

	/* demod adc */
	ret = rtl28xxu_wr_reg(d, SYS_SYS0, sys0);
	if (ret)
		goto err;

	/* tuner power, write GPIOs */
	ret = rtl28xxu_wr_reg(d, SYS_GPIO_OUT_VAL, gpio);
	if (ret)
		goto err;

	/* streaming EP: stall & reset */
	ret = rtl28xxu_wr_regs(d, USB_EPA_CTL, epa_ctl, 2);
	if (ret)
		goto err;

	if (onoff)
		usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, 0x81));

	return ret;
err:
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}