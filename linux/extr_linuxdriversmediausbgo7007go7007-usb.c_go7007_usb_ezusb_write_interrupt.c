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
struct go7007_usb {int /*<<< orphan*/  usbdev; } ;
struct go7007 {int /*<<< orphan*/  dev; int /*<<< orphan*/ * usb_buf; struct go7007_usb* hpi_context; } ;
typedef  int /*<<< orphan*/  status_reg ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_STATUS_ADDR ; 
 int /*<<< orphan*/  INT_INDEX_ADDR ; 
 int /*<<< orphan*/  INT_PARAM_ADDR ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int go7007_usb_ezusb_write_interrupt(struct go7007 *go,
						int addr, int data)
{
	struct go7007_usb *usb = go->hpi_context;
	int i, r;
	u16 status_reg = 0;
	int timeout = 500;

	pr_debug("WriteInterrupt: %04x %04x\n", addr, data);

	for (i = 0; i < 100; ++i) {
		r = usb_control_msg(usb->usbdev,
				usb_rcvctrlpipe(usb->usbdev, 0), 0x14,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
				0, HPI_STATUS_ADDR, go->usb_buf,
				sizeof(status_reg), timeout);
		if (r < 0)
			break;
		status_reg = le16_to_cpu(*((__le16 *)go->usb_buf));
		if (!(status_reg & 0x0010))
			break;
		msleep(10);
	}
	if (r < 0)
		goto write_int_error;
	if (i == 100) {
		dev_err(go->dev, "device is hung, status reg = 0x%04x\n", status_reg);
		return -1;
	}
	r = usb_control_msg(usb->usbdev, usb_sndctrlpipe(usb->usbdev, 0), 0x12,
			USB_TYPE_VENDOR | USB_RECIP_DEVICE, data,
			INT_PARAM_ADDR, NULL, 0, timeout);
	if (r < 0)
		goto write_int_error;
	r = usb_control_msg(usb->usbdev, usb_sndctrlpipe(usb->usbdev, 0),
			0x12, USB_TYPE_VENDOR | USB_RECIP_DEVICE, addr,
			INT_INDEX_ADDR, NULL, 0, timeout);
	if (r < 0)
		goto write_int_error;
	return 0;

write_int_error:
	dev_err(go->dev, "error in WriteInterrupt: %d\n", r);
	return r;
}