#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct as10x_bus_adapter_t {TYPE_1__* usb_dev; int /*<<< orphan*/  cmd_xid; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS102_USB_DEVICE_RX_CTRL_CMD ; 
 int /*<<< orphan*/  AS102_USB_DEVICE_TX_CTRL_CMD ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as102_usb_xfer_cmd(struct as10x_bus_adapter_t *bus_adap,
			      unsigned char *send_buf, int send_buf_len,
			      unsigned char *recv_buf, int recv_buf_len)
{
	int ret = 0;

	if (send_buf != NULL) {
		ret = usb_control_msg(bus_adap->usb_dev,
				      usb_sndctrlpipe(bus_adap->usb_dev, 0),
				      AS102_USB_DEVICE_TX_CTRL_CMD,
				      USB_DIR_OUT | USB_TYPE_VENDOR |
				      USB_RECIP_DEVICE,
				      bus_adap->cmd_xid, /* value */
				      0, /* index */
				      send_buf, send_buf_len,
				      USB_CTRL_SET_TIMEOUT /* 200 */);
		if (ret < 0) {
			dev_dbg(&bus_adap->usb_dev->dev,
				"usb_control_msg(send) failed, err %i\n", ret);
			return ret;
		}

		if (ret != send_buf_len) {
			dev_dbg(&bus_adap->usb_dev->dev,
			"only wrote %d of %d bytes\n", ret, send_buf_len);
			return -1;
		}
	}

	if (recv_buf != NULL) {
#ifdef TRACE
		dev_dbg(bus_adap->usb_dev->dev,
			"want to read: %d bytes\n", recv_buf_len);
#endif
		ret = usb_control_msg(bus_adap->usb_dev,
				      usb_rcvctrlpipe(bus_adap->usb_dev, 0),
				      AS102_USB_DEVICE_RX_CTRL_CMD,
				      USB_DIR_IN | USB_TYPE_VENDOR |
				      USB_RECIP_DEVICE,
				      bus_adap->cmd_xid, /* value */
				      0, /* index */
				      recv_buf, recv_buf_len,
				      USB_CTRL_GET_TIMEOUT /* 200 */);
		if (ret < 0) {
			dev_dbg(&bus_adap->usb_dev->dev,
				"usb_control_msg(recv) failed, err %i\n", ret);
			return ret;
		}
#ifdef TRACE
		dev_dbg(bus_adap->usb_dev->dev,
			"read %d bytes\n", recv_buf_len);
#endif
	}

	return ret;
}