#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct urb {int interval; int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ start_frame; struct stk_camera* context; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_buffer_length; TYPE_2__* transfer_buffer; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; struct usb_device* dev; } ;
struct stk_camera {TYPE_2__* isobufs; int /*<<< orphan*/  isoc_ep; struct usb_device* udev; } ;
struct TYPE_5__ {struct urb* urb; struct TYPE_5__* data; } ;
struct TYPE_4__ {int offset; int length; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISO_BUFFER_SIZE ; 
 int ISO_FRAMES_PER_DESC ; 
 int ISO_MAX_FRAME_SIZE ; 
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  set_memallocd (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_isoc_handler ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk_prepare_iso(struct stk_camera *dev)
{
	void *kbuf;
	int i, j;
	struct urb *urb;
	struct usb_device *udev;

	if (dev == NULL)
		return -ENXIO;
	udev = dev->udev;

	if (dev->isobufs)
		pr_err("isobufs already allocated. Bad\n");
	else
		dev->isobufs = kcalloc(MAX_ISO_BUFS, sizeof(*dev->isobufs),
				       GFP_KERNEL);
	if (dev->isobufs == NULL) {
		pr_err("Unable to allocate iso buffers\n");
		return -ENOMEM;
	}
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		if (dev->isobufs[i].data == NULL) {
			kbuf = kzalloc(ISO_BUFFER_SIZE, GFP_KERNEL);
			if (kbuf == NULL) {
				pr_err("Failed to allocate iso buffer %d\n", i);
				goto isobufs_out;
			}
			dev->isobufs[i].data = kbuf;
		} else
			pr_err("isobuf data already allocated\n");
		if (dev->isobufs[i].urb == NULL) {
			urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
			if (urb == NULL)
				goto isobufs_out;
			dev->isobufs[i].urb = urb;
		} else {
			pr_err("Killing URB\n");
			usb_kill_urb(dev->isobufs[i].urb);
			urb = dev->isobufs[i].urb;
		}
		urb->interval = 1;
		urb->dev = udev;
		urb->pipe = usb_rcvisocpipe(udev, dev->isoc_ep);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = dev->isobufs[i].data;
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->complete = stk_isoc_handler;
		urb->context = dev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;

		for (j = 0; j < ISO_FRAMES_PER_DESC; j++) {
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = ISO_MAX_FRAME_SIZE;
		}
	}
	set_memallocd(dev);
	return 0;

isobufs_out:
	for (i = 0; i < MAX_ISO_BUFS && dev->isobufs[i].data; i++)
		kfree(dev->isobufs[i].data);
	for (i = 0; i < MAX_ISO_BUFS && dev->isobufs[i].urb; i++)
		usb_free_urb(dev->isobufs[i].urb);
	kfree(dev->isobufs);
	dev->isobufs = NULL;
	return -ENOMEM;
}