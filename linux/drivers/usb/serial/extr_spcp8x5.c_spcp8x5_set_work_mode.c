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
typedef  int /*<<< orphan*/  u16 ;
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct spcp8x5_private {int quirks; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_WORKING_MODE ; 
 int /*<<< orphan*/  SET_WORKING_MODE_TYPE ; 
 int SPCP825_QUIRK_NO_WORK_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct spcp8x5_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spcp8x5_set_work_mode(struct usb_serial_port *port, u16 value,
								 u16 index)
{
	struct spcp8x5_private *priv = usb_get_serial_port_data(port);
	struct usb_device *dev = port->serial->dev;
	int ret;

	if (priv->quirks & SPCP825_QUIRK_NO_WORK_MODE)
		return;

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			      SET_WORKING_MODE_TYPE, SET_WORKING_MODE,
			      value, index, NULL, 0, 100);
	dev_dbg(&port->dev, "value = %#x , index = %#x\n", value, index);
	if (ret < 0)
		dev_err(&port->dev, "failed to set work mode: %d\n", ret);
}