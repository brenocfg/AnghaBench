#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_ftdi {TYPE_1__* udev; int /*<<< orphan*/  bulk_out_endpointAddr; } ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ftdi_elan_write_bulk_callback ; 
 char* usb_alloc_coherent (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct usb_ftdi*) ; 
 int /*<<< orphan*/  usb_free_coherent (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftdi_elan_synchronize_flush(struct usb_ftdi *ftdi)
{
	int retval;
	struct urb *urb;
	char *buf;
	int I = 257;
	int i = 0;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return -ENOMEM;
	buf = usb_alloc_coherent(ftdi->udev, I, GFP_KERNEL, &urb->transfer_dma);
	if (!buf) {
		dev_err(&ftdi->udev->dev, "could not get a buffer for flush sequence\n");
		usb_free_urb(urb);
		return -ENOMEM;
	}
	while (I-- > 0)
		buf[i++] = 0x55;
	usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
							   ftdi->bulk_out_endpointAddr), buf, i,
			  ftdi_elan_write_bulk_callback, ftdi);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	retval = usb_submit_urb(urb, GFP_KERNEL);
	if (retval) {
		dev_err(&ftdi->udev->dev, "failed to submit urb containing the flush sequence\n");
		usb_free_coherent(ftdi->udev, i, buf, urb->transfer_dma);
		usb_free_urb(urb);
		return -ENOMEM;
	}
	usb_free_urb(urb);
	return 0;
}