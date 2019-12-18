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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int /*<<< orphan*/  dev; struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct cp210x_port_private {int /*<<< orphan*/  bInterfaceNumber; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REQTYPE_INTERFACE_TO_HOST ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 struct cp210x_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp210x_read_reg_block(struct usb_serial_port *port, u8 req,
		void *buf, int bufsize)
{
	struct usb_serial *serial = port->serial;
	struct cp210x_port_private *port_priv = usb_get_serial_port_data(port);
	void *dmabuf;
	int result;

	dmabuf = kmalloc(bufsize, GFP_KERNEL);
	if (!dmabuf) {
		/*
		 * FIXME Some callers don't bother to check for error,
		 * at least give them consistent junk until they are fixed
		 */
		memset(buf, 0, bufsize);
		return -ENOMEM;
	}

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			req, REQTYPE_INTERFACE_TO_HOST, 0,
			port_priv->bInterfaceNumber, dmabuf, bufsize,
			USB_CTRL_SET_TIMEOUT);
	if (result == bufsize) {
		memcpy(buf, dmabuf, bufsize);
		result = 0;
	} else {
		dev_err(&port->dev, "failed get req 0x%x size %d status: %d\n",
				req, bufsize, result);
		if (result >= 0)
			result = -EIO;

		/*
		 * FIXME Some callers don't bother to check for error,
		 * at least give them consistent junk until they are fixed
		 */
		memset(buf, 0, bufsize);
	}

	kfree(dmabuf);

	return result;
}