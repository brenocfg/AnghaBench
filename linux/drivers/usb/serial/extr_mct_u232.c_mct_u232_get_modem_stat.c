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
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCT_U232_GET_MODEM_STAT_REQUEST ; 
 int MCT_U232_GET_MODEM_STAT_SIZE ; 
 int /*<<< orphan*/  MCT_U232_GET_REQUEST_TYPE ; 
 int /*<<< orphan*/  MCT_U232_MAX_SIZE ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mct_u232_get_modem_stat(struct usb_serial_port *port,
				   unsigned char *msr)
{
	int rc;
	unsigned char *buf;

	buf = kmalloc(MCT_U232_MAX_SIZE, GFP_KERNEL);
	if (buf == NULL) {
		*msr = 0;
		return -ENOMEM;
	}
	rc = usb_control_msg(port->serial->dev, usb_rcvctrlpipe(port->serial->dev, 0),
			MCT_U232_GET_MODEM_STAT_REQUEST,
			MCT_U232_GET_REQUEST_TYPE,
			0, 0, buf, MCT_U232_GET_MODEM_STAT_SIZE,
			WDR_TIMEOUT);
	if (rc < MCT_U232_GET_MODEM_STAT_SIZE) {
		dev_err(&port->dev, "Get MODEM STATus failed (error = %d)\n", rc);

		if (rc >= 0)
			rc = -EIO;

		*msr = 0;
	} else {
		*msr = buf[0];
	}
	dev_dbg(&port->dev, "get_modem_stat: 0x%x\n", *msr);
	kfree(buf);
	return rc;
}