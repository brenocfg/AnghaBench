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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;
struct rtl_priv {TYPE_1__ io; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ REALTEK_USB_VENQT_CMD_IDX ; 
 int /*<<< orphan*/  REALTEK_USB_VENQT_CMD_REQ ; 
 int /*<<< orphan*/  REALTEK_USB_VENQT_WRITE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _usb_writen_sync(struct rtl_priv *rtlpriv, u32 addr, void *data,
			     u16 len)
{
	struct device *dev = rtlpriv->io.dev;
	struct usb_device *udev = to_usb_device(dev);
	u8 request = REALTEK_USB_VENQT_CMD_REQ;
	u8 reqtype =  REALTEK_USB_VENQT_WRITE;
	u16 wvalue;
	u16 index = REALTEK_USB_VENQT_CMD_IDX;
	int pipe = usb_sndctrlpipe(udev, 0); /* write_out */
	u8 *buffer;

	wvalue = (u16)(addr & 0x0000ffff);
	buffer = kmemdup(data, len, GFP_ATOMIC);
	if (!buffer)
		return;
	usb_control_msg(udev, pipe, request, reqtype, wvalue,
			index, buffer, len, 50);

	kfree(buffer);
}