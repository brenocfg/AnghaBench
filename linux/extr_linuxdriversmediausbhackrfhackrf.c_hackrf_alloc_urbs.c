#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * usb_complete_t ;
struct hackrf_dev {int /*<<< orphan*/  urbs_initialized; int /*<<< orphan*/ * dma_addr; TYPE_1__** urb_list; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  udev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_BUFFER_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_BULK_BUFS ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hackrf_urb_complete_in ; 
 int /*<<< orphan*/  hackrf_urb_complete_out ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hackrf_dev*) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 unsigned int usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hackrf_alloc_urbs(struct hackrf_dev *dev, bool rcv)
{
	int i, j;
	unsigned int pipe;
	usb_complete_t complete;

	if (rcv) {
		pipe = usb_rcvbulkpipe(dev->udev, 0x81);
		complete = &hackrf_urb_complete_in;
	} else {
		pipe = usb_sndbulkpipe(dev->udev, 0x02);
		complete = &hackrf_urb_complete_out;
	}

	/* allocate the URBs */
	for (i = 0; i < MAX_BULK_BUFS; i++) {
		dev_dbg(dev->dev, "alloc urb=%d\n", i);
		dev->urb_list[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!dev->urb_list[i]) {
			for (j = 0; j < i; j++)
				usb_free_urb(dev->urb_list[j]);
			return -ENOMEM;
		}
		usb_fill_bulk_urb(dev->urb_list[i],
				dev->udev,
				pipe,
				dev->buf_list[i],
				BULK_BUFFER_SIZE,
				complete, dev);

		dev->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		dev->urb_list[i]->transfer_dma = dev->dma_addr[i];
		dev->urbs_initialized++;
	}

	return 0;
}