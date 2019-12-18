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
struct go7007_usb {int /*<<< orphan*/  usbdev; TYPE_1__* board; } ;
struct go7007 {struct go7007_usb* hpi_context; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int GO7007_USB_EZUSB ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*,int) ; 
 int usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int go7007_usb_send_firmware(struct go7007 *go, u8 *data, int len)
{
	struct go7007_usb *usb = go->hpi_context;
	int transferred, pipe;
	int timeout = 500;

	pr_debug("DownloadBuffer sending %d bytes\n", len);

	if (usb->board->flags & GO7007_USB_EZUSB)
		pipe = usb_sndbulkpipe(usb->usbdev, 2);
	else
		pipe = usb_sndbulkpipe(usb->usbdev, 3);

	return usb_bulk_msg(usb->usbdev, pipe, data, len,
					&transferred, timeout);
}