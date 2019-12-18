#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {scalar_t__ transfer_flags; } ;
struct cx231xx_dmaqueue {int current_field; int bytes_left_in_line; int /*<<< orphan*/  wq; scalar_t__* partial_buf; scalar_t__ lines_completed; int /*<<< orphan*/  lines_per_field; scalar_t__ last_sav; scalar_t__ is_partial_line; scalar_t__ pos; } ;
struct TYPE_3__ {int (* bulk_copy ) (struct cx231xx*,struct urb*) ;int num_bufs; int max_pkt_size; struct urb** urb; int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/ * buf; } ;
struct TYPE_4__ {TYPE_1__ bulk_ctl; int /*<<< orphan*/  end_point_addr; struct cx231xx_dmaqueue vidq; } ;
struct cx231xx {int width; int norm; int /*<<< orphan*/  dev; TYPE_2__ vbi_mode; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NTSC_VBI_LINES ; 
 int /*<<< orphan*/  PAL_VBI_LINES ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  Vbi ; 
 int /*<<< orphan*/  cx231xx_capture_start (struct cx231xx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_irq_vbi_callback ; 
 int /*<<< orphan*/  cx231xx_uninit_vbi_isoc (struct cx231xx*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cx231xx_dmaqueue*) ; 
 int usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int cx231xx_init_vbi_isoc(struct cx231xx *dev, int max_packets,
			  int num_bufs, int max_pkt_size,
			  int (*bulk_copy) (struct cx231xx *dev,
					    struct urb *urb))
{
	struct cx231xx_dmaqueue *dma_q = &dev->vbi_mode.vidq;
	int i;
	int sb_size, pipe;
	struct urb *urb;
	int rc;

	dev_dbg(dev->dev, "called cx231xx_vbi_isoc\n");

	/* De-allocates all pending stuff */
	cx231xx_uninit_vbi_isoc(dev);

	/* clear if any halt */
	usb_clear_halt(dev->udev,
		       usb_rcvbulkpipe(dev->udev,
				       dev->vbi_mode.end_point_addr));

	dev->vbi_mode.bulk_ctl.bulk_copy = bulk_copy;
	dev->vbi_mode.bulk_ctl.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_partial_line = 0;
	dma_q->last_sav = 0;
	dma_q->current_field = -1;
	dma_q->bytes_left_in_line = dev->width << 1;
	dma_q->lines_per_field = ((dev->norm & V4L2_STD_625_50) ?
				  PAL_VBI_LINES : NTSC_VBI_LINES);
	dma_q->lines_completed = 0;
	for (i = 0; i < 8; i++)
		dma_q->partial_buf[i] = 0;

	dev->vbi_mode.bulk_ctl.urb = kcalloc(num_bufs, sizeof(void *),
					     GFP_KERNEL);
	if (!dev->vbi_mode.bulk_ctl.urb) {
		dev_err(dev->dev,
			"cannot alloc memory for usb buffers\n");
		return -ENOMEM;
	}

	dev->vbi_mode.bulk_ctl.transfer_buffer =
	    kcalloc(num_bufs, sizeof(void *), GFP_KERNEL);
	if (!dev->vbi_mode.bulk_ctl.transfer_buffer) {
		dev_err(dev->dev,
			"cannot allocate memory for usbtransfer\n");
		kfree(dev->vbi_mode.bulk_ctl.urb);
		return -ENOMEM;
	}

	dev->vbi_mode.bulk_ctl.max_pkt_size = max_pkt_size;
	dev->vbi_mode.bulk_ctl.buf = NULL;

	sb_size = max_packets * dev->vbi_mode.bulk_ctl.max_pkt_size;

	/* allocate urbs and transfer buffers */
	for (i = 0; i < dev->vbi_mode.bulk_ctl.num_bufs; i++) {

		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			cx231xx_uninit_vbi_isoc(dev);
			return -ENOMEM;
		}
		dev->vbi_mode.bulk_ctl.urb[i] = urb;
		urb->transfer_flags = 0;

		dev->vbi_mode.bulk_ctl.transfer_buffer[i] =
		    kzalloc(sb_size, GFP_KERNEL);
		if (!dev->vbi_mode.bulk_ctl.transfer_buffer[i]) {
			dev_err(dev->dev,
				"unable to allocate %i bytes for transfer buffer %i%s\n",
				sb_size, i,
				in_interrupt() ? " while in int" : "");
			cx231xx_uninit_vbi_isoc(dev);
			return -ENOMEM;
		}

		pipe = usb_rcvbulkpipe(dev->udev, dev->vbi_mode.end_point_addr);
		usb_fill_bulk_urb(urb, dev->udev, pipe,
				  dev->vbi_mode.bulk_ctl.transfer_buffer[i],
				  sb_size, cx231xx_irq_vbi_callback, dma_q);
	}

	init_waitqueue_head(&dma_q->wq);

	/* submit urbs and enables IRQ */
	for (i = 0; i < dev->vbi_mode.bulk_ctl.num_bufs; i++) {
		rc = usb_submit_urb(dev->vbi_mode.bulk_ctl.urb[i], GFP_ATOMIC);
		if (rc) {
			dev_err(dev->dev,
				"submit of urb %i failed (error=%i)\n", i, rc);
			cx231xx_uninit_vbi_isoc(dev);
			return rc;
		}
	}

	cx231xx_capture_start(dev, 1, Vbi);

	return 0;
}