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
struct usb_serial_port {TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct ftdi_private {int /*<<< orphan*/  interface; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FTDI_SIO_GET_LATENCY_TIMER_REQUEST ; 
 int /*<<< orphan*/  FTDI_SIO_GET_LATENCY_TIMER_REQUEST_TYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _read_latency_timer(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	struct usb_device *udev = port->serial->dev;
	unsigned char *buf;
	int rv;

	buf = kmalloc(1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	rv = usb_control_msg(udev,
			     usb_rcvctrlpipe(udev, 0),
			     FTDI_SIO_GET_LATENCY_TIMER_REQUEST,
			     FTDI_SIO_GET_LATENCY_TIMER_REQUEST_TYPE,
			     0, priv->interface,
			     buf, 1, WDR_TIMEOUT);
	if (rv < 1) {
		if (rv >= 0)
			rv = -EIO;
	} else {
		rv = buf[0];
	}

	kfree(buf);

	return rv;
}