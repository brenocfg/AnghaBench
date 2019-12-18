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
typedef  int u16 ;
struct vprbrd_i2c_status {int status; } ;
struct vprbrd {int /*<<< orphan*/  usb_dev; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; scalar_t__ algo_data; } ;

/* Variables and functions */
 int EPROTO ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  VPRBRD_USB_REQUEST_I2C ; 
 int /*<<< orphan*/  VPRBRD_USB_TIMEOUT_MS ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_IN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct vprbrd_i2c_status*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vprbrd_i2c_status(struct i2c_adapter *i2c,
	struct vprbrd_i2c_status *status, bool prev_error)
{
	u16 bytes_xfer;
	int ret;
	struct vprbrd *vb = (struct vprbrd *)i2c->algo_data;

	/* check for protocol error */
	bytes_xfer = sizeof(struct vprbrd_i2c_status);

	ret = usb_control_msg(vb->usb_dev, usb_rcvctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_I2C, VPRBRD_USB_TYPE_IN, 0x0000, 0x0000,
		status, bytes_xfer, VPRBRD_USB_TIMEOUT_MS);

	if (ret != bytes_xfer)
		prev_error = true;

	if (prev_error) {
		dev_err(&i2c->dev, "failure in usb communication\n");
		return -EREMOTEIO;
	}

	dev_dbg(&i2c->dev, "  status = %d\n", status->status);
	if (status->status != 0x00) {
		dev_err(&i2c->dev, "failure: i2c protocol error\n");
		return -EPROTO;
	}
	return 0;
}