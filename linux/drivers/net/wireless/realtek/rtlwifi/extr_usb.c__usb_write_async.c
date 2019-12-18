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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ REALTEK_USB_VENQT_CMD_IDX ; 
 int /*<<< orphan*/  REALTEK_USB_VENQT_CMD_REQ ; 
 int /*<<< orphan*/  _usbctrl_vendorreq_async_write (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void _usb_write_async(struct usb_device *udev, u32 addr, u32 val,
			     u16 len)
{
	u8 request;
	u16 wvalue;
	u16 index;
	__le32 data;

	request = REALTEK_USB_VENQT_CMD_REQ;
	index = REALTEK_USB_VENQT_CMD_IDX; /* n/a */
	wvalue = (u16)(addr&0x0000ffff);
	data = cpu_to_le32(val);
	_usbctrl_vendorreq_async_write(udev, request, wvalue, index, &data,
				       len);
}