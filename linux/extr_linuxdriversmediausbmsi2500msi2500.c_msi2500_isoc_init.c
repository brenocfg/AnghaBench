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
struct urb {int interval; int transfer_flags; int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ start_frame; struct msi2500_dev* context; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;
struct msi2500_dev {struct urb** urbs; int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; scalar_t__ isoc_errors; } ;
struct TYPE_2__ {int offset; int length; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISO_BUFFER_SIZE ; 
 int ISO_FRAMES_PER_DESC ; 
 int ISO_MAX_FRAME_SIZE ; 
 int MAX_ISO_BUFS ; 
 int URB_ISO_ASAP ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  msi2500_isoc_cleanup (struct msi2500_dev*) ; 
 int /*<<< orphan*/  msi2500_isoc_handler ; 
 int /*<<< orphan*/ * usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msi2500_isoc_init(struct msi2500_dev *dev)
{
	struct urb *urb;
	int i, j, ret;

	dev_dbg(dev->dev, "\n");

	dev->isoc_errors = 0;

	ret = usb_set_interface(dev->udev, 0, 1);
	if (ret)
		return ret;

	/* Allocate and init Isochronuous urbs */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
		if (urb == NULL) {
			msi2500_isoc_cleanup(dev);
			return -ENOMEM;
		}
		dev->urbs[i] = urb;
		dev_dbg(dev->dev, "Allocated URB at 0x%p\n", urb);

		urb->interval = 1;
		urb->dev = dev->udev;
		urb->pipe = usb_rcvisocpipe(dev->udev, 0x81);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_buffer = usb_alloc_coherent(dev->udev,
				ISO_BUFFER_SIZE,
				GFP_KERNEL, &urb->transfer_dma);
		if (urb->transfer_buffer == NULL) {
			dev_err(dev->dev,
				"Failed to allocate urb buffer %d\n", i);
			msi2500_isoc_cleanup(dev);
			return -ENOMEM;
		}
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->complete = msi2500_isoc_handler;
		urb->context = dev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;
		for (j = 0; j < ISO_FRAMES_PER_DESC; j++) {
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = ISO_MAX_FRAME_SIZE;
		}
	}

	/* link */
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		ret = usb_submit_urb(dev->urbs[i], GFP_KERNEL);
		if (ret) {
			dev_err(dev->dev,
				"usb_submit_urb %d failed with error %d\n",
				i, ret);
			msi2500_isoc_cleanup(dev);
			return ret;
		}
		dev_dbg(dev->dev, "URB 0x%p submitted.\n", dev->urbs[i]);
	}

	/* All is done... */
	return 0;
}