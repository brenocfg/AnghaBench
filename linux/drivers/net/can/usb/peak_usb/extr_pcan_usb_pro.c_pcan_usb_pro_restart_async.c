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
struct urb {int dummy; } ;
struct peak_usb_device {int /*<<< orphan*/  udev; int /*<<< orphan*/  ctrl_idx; } ;
struct pcan_usb_pro_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCAN_USBPRO_EP_CMDOUT ; 
 int /*<<< orphan*/  PCAN_USBPRO_SETBUSACT ; 
 int /*<<< orphan*/  PCAN_USB_MAX_CMD_LEN ; 
 int /*<<< orphan*/  pcan_msg_add_rec (struct pcan_usb_pro_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcan_msg_init_empty (struct pcan_usb_pro_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_usb_pro_restart_complete ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct peak_usb_device*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_pro_restart_async(struct peak_usb_device *dev,
				      struct urb *urb, u8 *buf)
{
	struct pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETBUSACT, dev->ctrl_idx, 1);

	usb_fill_bulk_urb(urb, dev->udev,
			usb_sndbulkpipe(dev->udev, PCAN_USBPRO_EP_CMDOUT),
			buf, PCAN_USB_MAX_CMD_LEN,
			pcan_usb_pro_restart_complete, dev);

	return usb_submit_urb(urb, GFP_ATOMIC);
}