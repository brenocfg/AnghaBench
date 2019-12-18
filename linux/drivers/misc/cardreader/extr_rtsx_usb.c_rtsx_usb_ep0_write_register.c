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
typedef  int u16 ;
struct rtsx_ucr {int /*<<< orphan*/  pusb_dev; } ;

/* Variables and functions */
 int EP0_OP_SHIFT ; 
 int EP0_WRITE_REG_CMD ; 
 int /*<<< orphan*/  RTSX_USB_REQ_REG_OP ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int swab16 (int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtsx_usb_ep0_write_register(struct rtsx_ucr *ucr, u16 addr,
		u8 mask, u8 data)
{
	u16 value, index;

	addr |= EP0_WRITE_REG_CMD << EP0_OP_SHIFT;
	value = swab16(addr);
	index = mask | data << 8;

	return usb_control_msg(ucr->pusb_dev,
			usb_sndctrlpipe(ucr->pusb_dev, 0), RTSX_USB_REQ_REG_OP,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, NULL, 0, 100);
}