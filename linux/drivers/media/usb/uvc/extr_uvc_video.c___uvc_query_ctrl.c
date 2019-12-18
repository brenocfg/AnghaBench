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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct uvc_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,int,int,void*,int /*<<< orphan*/ ,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __uvc_query_ctrl(struct uvc_device *dev, u8 query, u8 unit,
			u8 intfnum, u8 cs, void *data, u16 size,
			int timeout)
{
	u8 type = USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	unsigned int pipe;

	pipe = (query & 0x80) ? usb_rcvctrlpipe(dev->udev, 0)
			      : usb_sndctrlpipe(dev->udev, 0);
	type |= (query & 0x80) ? USB_DIR_IN : USB_DIR_OUT;

	return usb_control_msg(dev->udev, pipe, query, type, cs << 8,
			unit << 8 | intfnum, data, size, timeout);
}