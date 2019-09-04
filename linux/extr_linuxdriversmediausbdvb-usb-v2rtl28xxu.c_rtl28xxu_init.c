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
 int /*<<< orphan*/  USB_EPA_FIFO_CFG ; 
 int /*<<< orphan*/  USB_EPA_MAXPKT ; 
 int /*<<< orphan*/  USB_SYSCTL_0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int rtl28xxu_rd_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int rtl28xxu_wr_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 
 int rtl28xxu_wr_regs (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int rtl28xxu_init(struct dvb_usb_device *d)
{
	int ret;
	u8 val;

	dev_dbg(&d->intf->dev, "\n");

	/* init USB endpoints */
	ret = rtl28xxu_rd_reg(d, USB_SYSCTL_0, &val);
	if (ret)
		goto err;

	/* enable DMA and Full Packet Mode*/
	val |= 0x09;
	ret = rtl28xxu_wr_reg(d, USB_SYSCTL_0, val);
	if (ret)
		goto err;

	/* set EPA maximum packet size to 0x0200 */
	ret = rtl28xxu_wr_regs(d, USB_EPA_MAXPKT, "\x00\x02\x00\x00", 4);
	if (ret)
		goto err;

	/* change EPA FIFO length */
	ret = rtl28xxu_wr_regs(d, USB_EPA_FIFO_CFG, "\x14\x00\x00\x00", 4);
	if (ret)
		goto err;

	return ret;
err:
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}