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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct spcp8x5_private {int quirks; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GET_UART_STATUS ; 
 int /*<<< orphan*/  GET_UART_STATUS_MSR ; 
 int /*<<< orphan*/  GET_UART_STATUS_TYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPCP825_QUIRK_NO_UART_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 struct spcp8x5_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spcp8x5_get_msr(struct usb_serial_port *port, u8 *status)
{
	struct spcp8x5_private *priv = usb_get_serial_port_data(port);
	struct usb_device *dev = port->serial->dev;
	u8 *buf;
	int ret;

	if (priv->quirks & SPCP825_QUIRK_NO_UART_STATUS)
		return -EPERM;

	buf = kzalloc(1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			      GET_UART_STATUS, GET_UART_STATUS_TYPE,
			      0, GET_UART_STATUS_MSR, buf, 1, 100);
	if (ret < 1) {
		dev_err(&port->dev, "failed to get modem status: %d\n", ret);
		if (ret >= 0)
			ret = -EIO;
		goto out;
	}

	dev_dbg(&port->dev, "0xc0:0x22:0:6  %d - 0x02%x\n", ret, *buf);
	*status = *buf;
	ret = 0;
out:
	kfree(buf);

	return ret;
}