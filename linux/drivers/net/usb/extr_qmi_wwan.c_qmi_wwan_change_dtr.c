#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {TYPE_3__* intf; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CDC_REQ_SET_CONTROL_LINE_STATE ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int usbnet_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qmi_wwan_change_dtr(struct usbnet *dev, bool on)
{
	u8 intf = dev->intf->cur_altsetting->desc.bInterfaceNumber;

	return usbnet_write_cmd(dev, USB_CDC_REQ_SET_CONTROL_LINE_STATE,
				USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				on ? 0x01 : 0x00, intf, NULL, 0);
}