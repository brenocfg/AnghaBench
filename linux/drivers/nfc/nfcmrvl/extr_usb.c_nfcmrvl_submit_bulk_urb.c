#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct nfcmrvl_usb_drv_data {TYPE_2__* udev; int /*<<< orphan*/  bulk_anchor; TYPE_1__* bulk_rx_ep; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int NFCMRVL_NCI_MAX_EVENT_SIZE ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*,struct urb*,int) ; 
 int /*<<< orphan*/  nfcmrvl_bulk_complete ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_2__*,unsigned int,unsigned char*,int,int /*<<< orphan*/ ,struct nfcmrvl_usb_drv_data*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_mark_last_busy (TYPE_2__*) ; 
 unsigned int usb_rcvbulkpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int
nfcmrvl_submit_bulk_urb(struct nfcmrvl_usb_drv_data *drv_data, gfp_t mem_flags)
{
	struct urb *urb;
	unsigned char *buf;
	unsigned int pipe;
	int err, size = NFCMRVL_NCI_MAX_EVENT_SIZE;

	if (!drv_data->bulk_rx_ep)
		return -ENODEV;

	urb = usb_alloc_urb(0, mem_flags);
	if (!urb)
		return -ENOMEM;

	buf = kmalloc(size, mem_flags);
	if (!buf) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	pipe = usb_rcvbulkpipe(drv_data->udev,
			       drv_data->bulk_rx_ep->bEndpointAddress);

	usb_fill_bulk_urb(urb, drv_data->udev, pipe, buf, size,
			  nfcmrvl_bulk_complete, drv_data);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_mark_last_busy(drv_data->udev);
	usb_anchor_urb(urb, &drv_data->bulk_anchor);

	err = usb_submit_urb(urb, mem_flags);
	if (err) {
		if (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p submission failed (%d)\n", urb, -err);
		usb_unanchor_urb(urb);
	}

	usb_free_urb(urb);

	return err;
}