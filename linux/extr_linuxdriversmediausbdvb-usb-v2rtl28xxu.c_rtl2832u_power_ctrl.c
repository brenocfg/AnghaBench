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
struct dvb_usb_device {TYPE_1__* intf; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_DEMOD_CTL ; 
 int /*<<< orphan*/  SYS_DEMOD_CTL1 ; 
 int /*<<< orphan*/  SYS_GPIO_OUT_VAL ; 
 int /*<<< orphan*/  USB_EPA_CTL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int rtl28xxu_wr_reg_mask (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int) ; 
 int rtl28xxu_wr_regs (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,int) ; 
 int usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl2832u_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	int ret;

	dev_dbg(&d->intf->dev, "onoff=%d\n", onoff);

	if (onoff) {
		/* GPIO3=1, GPIO4=0 */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x08, 0x18);
		if (ret)
			goto err;

		/* suspend? */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL1, 0x00, 0x10);
		if (ret)
			goto err;

		/* enable PLL */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, 0x80, 0x80);
		if (ret)
			goto err;

		/* disable reset */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, 0x20, 0x20);
		if (ret)
			goto err;

		/* streaming EP: clear stall & reset */
		ret = rtl28xxu_wr_regs(d, USB_EPA_CTL, "\x00\x00", 2);
		if (ret)
			goto err;

		ret = usb_clear_halt(d->udev, usb_rcvbulkpipe(d->udev, 0x81));
		if (ret)
			goto err;
	} else {
		/* GPIO4=1 */
		ret = rtl28xxu_wr_reg_mask(d, SYS_GPIO_OUT_VAL, 0x10, 0x10);
		if (ret)
			goto err;

		/* disable PLL */
		ret = rtl28xxu_wr_reg_mask(d, SYS_DEMOD_CTL, 0x00, 0x80);
		if (ret)
			goto err;

		/* streaming EP: set stall & reset */
		ret = rtl28xxu_wr_regs(d, USB_EPA_CTL, "\x10\x02", 2);
		if (ret)
			goto err;
	}

	return ret;
err:
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}