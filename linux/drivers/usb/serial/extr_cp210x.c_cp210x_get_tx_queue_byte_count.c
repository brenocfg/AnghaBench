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
typedef  int /*<<< orphan*/  u32 ;
struct usb_serial_port {int /*<<< orphan*/  dev; struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct cp210x_port_private {int /*<<< orphan*/  bInterfaceNumber; } ;
struct cp210x_comm_status {int /*<<< orphan*/  ulAmountInOutQueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP210X_GET_COMM_STATUS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REQTYPE_INTERFACE_TO_HOST ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct cp210x_comm_status*) ; 
 struct cp210x_comm_status* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cp210x_comm_status*,int,int /*<<< orphan*/ ) ; 
 struct cp210x_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp210x_get_tx_queue_byte_count(struct usb_serial_port *port,
		u32 *count)
{
	struct usb_serial *serial = port->serial;
	struct cp210x_port_private *port_priv = usb_get_serial_port_data(port);
	struct cp210x_comm_status *sts;
	int result;

	sts = kmalloc(sizeof(*sts), GFP_KERNEL);
	if (!sts)
		return -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			CP210X_GET_COMM_STATUS, REQTYPE_INTERFACE_TO_HOST,
			0, port_priv->bInterfaceNumber, sts, sizeof(*sts),
			USB_CTRL_GET_TIMEOUT);
	if (result == sizeof(*sts)) {
		*count = le32_to_cpu(sts->ulAmountInOutQueue);
		result = 0;
	} else {
		dev_err(&port->dev, "failed to get comm status: %d\n", result);
		if (result >= 0)
			result = -EIO;
	}

	kfree(sts);

	return result;
}