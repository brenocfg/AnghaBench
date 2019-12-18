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
struct airspy {int /*<<< orphan*/  urbs_initialized; int /*<<< orphan*/ * dma_addr; TYPE_1__** urb_list; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  udev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_BUFFER_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_BULK_BUFS ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  airspy_urb_complete ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct airspy*) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int airspy_alloc_urbs(struct airspy *s)
{
	int i, j;

	/* allocate the URBs */
	for (i = 0; i < MAX_BULK_BUFS; i++) {
		dev_dbg(s->dev, "alloc urb=%d\n", i);
		s->urb_list[i] = usb_alloc_urb(0, GFP_ATOMIC);
		if (!s->urb_list[i]) {
			for (j = 0; j < i; j++)
				usb_free_urb(s->urb_list[j]);
			return -ENOMEM;
		}
		usb_fill_bulk_urb(s->urb_list[i],
				s->udev,
				usb_rcvbulkpipe(s->udev, 0x81),
				s->buf_list[i],
				BULK_BUFFER_SIZE,
				airspy_urb_complete, s);

		s->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		s->urb_list[i]->transfer_dma = s->dma_addr[i];
		s->urbs_initialized++;
	}

	return 0;
}