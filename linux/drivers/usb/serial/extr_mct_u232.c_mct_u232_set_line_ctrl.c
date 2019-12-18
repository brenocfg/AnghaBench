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
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCT_U232_MAX_SIZE ; 
 int /*<<< orphan*/  MCT_U232_SET_LINE_CTRL_REQUEST ; 
 int /*<<< orphan*/  MCT_U232_SET_LINE_CTRL_SIZE ; 
 int /*<<< orphan*/  MCT_U232_SET_REQUEST_TYPE ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mct_u232_set_line_ctrl(struct usb_serial_port *port,
				  unsigned char lcr)
{
	int rc;
	unsigned char *buf;

	buf = kmalloc(MCT_U232_MAX_SIZE, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	buf[0] = lcr;
	rc = usb_control_msg(port->serial->dev, usb_sndctrlpipe(port->serial->dev, 0),
			MCT_U232_SET_LINE_CTRL_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_LINE_CTRL_SIZE,
			WDR_TIMEOUT);
	if (rc < 0)
		dev_err(&port->dev, "Set LINE CTRL 0x%x failed (error = %d)\n", lcr, rc);
	dev_dbg(&port->dev, "set_line_ctrl: 0x%x\n", lcr);
	kfree(buf);
	return rc;
}