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
struct go7007_usb {int /*<<< orphan*/  usbdev; } ;
struct go7007 {int* usb_buf; int /*<<< orphan*/  dev; struct go7007_usb* hpi_context; } ;

/* Variables and functions */
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int go7007_usb_onboard_write_interrupt(struct go7007 *go,
						int addr, int data)
{
	struct go7007_usb *usb = go->hpi_context;
	int r;
	int timeout = 500;

	pr_debug("WriteInterrupt: %04x %04x\n", addr, data);

	go->usb_buf[0] = data & 0xff;
	go->usb_buf[1] = data >> 8;
	go->usb_buf[2] = addr & 0xff;
	go->usb_buf[3] = addr >> 8;
	go->usb_buf[4] = go->usb_buf[5] = go->usb_buf[6] = go->usb_buf[7] = 0;
	r = usb_control_msg(usb->usbdev, usb_sndctrlpipe(usb->usbdev, 2), 0x00,
			USB_TYPE_VENDOR | USB_RECIP_ENDPOINT, 0x55aa,
			0xf0f0, go->usb_buf, 8, timeout);
	if (r < 0) {
		dev_err(go->dev, "error in WriteInterrupt: %d\n", r);
		return r;
	}
	return 0;
}