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
typedef  int u32 ;
struct usb_tx {int /*<<< orphan*/  urb; int /*<<< orphan*/  buf; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gdm_usb_send_complete ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_tx*) ; 
 int /*<<< orphan*/  usb_mark_last_busy (struct usb_device*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_tx_packet(struct usb_device *usbdev, struct usb_tx *t, u32 len)
{
	int ret = 0;

	if (!(len % 512))
		len++;

	usb_fill_bulk_urb(t->urb,
			  usbdev,
			  usb_sndbulkpipe(usbdev, 2),
			  t->buf,
			  len,
			  gdm_usb_send_complete,
			  t);

	ret = usb_submit_urb(t->urb, GFP_ATOMIC);

	if (ret)
		dev_err(&usbdev->dev, "usb_submit_urb failed: %d\n",
			ret);

	usb_mark_last_busy(usbdev);

	return ret;
}