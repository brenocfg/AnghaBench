#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wa_xfer_hwaiso {int dummy; } ;
struct wa_xfer_ctl {int dummy; } ;
struct wa_xfer_bi {int dummy; } ;
struct wa_xfer {int is_inbound; int is_dma; int seg_size; int segs; TYPE_4__* wa; TYPE_2__* ep; struct urb* urb; } ;
struct TYPE_10__ {int bmAttribute; int /*<<< orphan*/  wBlocks; int /*<<< orphan*/  wMaxPacketSize; } ;
struct wa_rpipe {TYPE_5__ descr; } ;
struct urb {int pipe; int transfer_flags; int number_of_packets; int transfer_buffer_length; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum wa_xfer_type { ____Placeholder_wa_xfer_type } wa_xfer_type ;
struct TYPE_9__ {TYPE_3__* wa_descr; TYPE_1__* usb_iface; } ;
struct TYPE_8__ {int bRPipeBlockSize; } ;
struct TYPE_7__ {struct wa_rpipe* hcpriv; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DIV_ROUND_UP (int,size_t) ; 
 int EINVAL ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 int USB_DIR_IN ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 size_t WA_SEGS_MAX ; 
 int WA_XFER_TYPE_BI ; 
 int WA_XFER_TYPE_CTL ; 
 int WA_XFER_TYPE_ISO ; 
 scalar_t__ __wa_seg_calculate_isoc_frame_count (struct wa_xfer*,int,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,size_t) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t __wa_xfer_setup_sizes(struct wa_xfer *xfer,
				     enum wa_xfer_type *pxfer_type)
{
	ssize_t result;
	struct device *dev = &xfer->wa->usb_iface->dev;
	size_t maxpktsize;
	struct urb *urb = xfer->urb;
	struct wa_rpipe *rpipe = xfer->ep->hcpriv;

	switch (rpipe->descr.bmAttribute & 0x3) {
	case USB_ENDPOINT_XFER_CONTROL:
		*pxfer_type = WA_XFER_TYPE_CTL;
		result = sizeof(struct wa_xfer_ctl);
		break;
	case USB_ENDPOINT_XFER_INT:
	case USB_ENDPOINT_XFER_BULK:
		*pxfer_type = WA_XFER_TYPE_BI;
		result = sizeof(struct wa_xfer_bi);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		*pxfer_type = WA_XFER_TYPE_ISO;
		result = sizeof(struct wa_xfer_hwaiso);
		break;
	default:
		/* never happens */
		BUG();
		result = -EINVAL;	/* shut gcc up */
	}
	xfer->is_inbound = urb->pipe & USB_DIR_IN ? 1 : 0;
	xfer->is_dma = urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP ? 1 : 0;

	maxpktsize = le16_to_cpu(rpipe->descr.wMaxPacketSize);
	xfer->seg_size = le16_to_cpu(rpipe->descr.wBlocks)
		* 1 << (xfer->wa->wa_descr->bRPipeBlockSize - 1);
	/* Compute the segment size and make sure it is a multiple of
	 * the maxpktsize (WUSB1.0[8.3.3.1])...not really too much of
	 * a check (FIXME) */
	if (xfer->seg_size < maxpktsize) {
		dev_err(dev,
			"HW BUG? seg_size %zu smaller than maxpktsize %zu\n",
			xfer->seg_size, maxpktsize);
		result = -EINVAL;
		goto error;
	}
	xfer->seg_size = (xfer->seg_size / maxpktsize) * maxpktsize;
	if ((rpipe->descr.bmAttribute & 0x3) == USB_ENDPOINT_XFER_ISOC) {
		int index = 0;

		xfer->segs = 0;
		/*
		 * loop over urb->number_of_packets to determine how many
		 * xfer segments will be needed to send the isoc frames.
		 */
		while (index < urb->number_of_packets) {
			int seg_size; /* don't care. */
			index += __wa_seg_calculate_isoc_frame_count(xfer,
					index, &seg_size);
			++xfer->segs;
		}
	} else {
		xfer->segs = DIV_ROUND_UP(urb->transfer_buffer_length,
						xfer->seg_size);
		if (xfer->segs == 0 && *pxfer_type == WA_XFER_TYPE_CTL)
			xfer->segs = 1;
	}

	if (xfer->segs > WA_SEGS_MAX) {
		dev_err(dev, "BUG? oops, number of segments %zu bigger than %d\n",
			(urb->transfer_buffer_length/xfer->seg_size),
			WA_SEGS_MAX);
		result = -EINVAL;
		goto error;
	}
error:
	return result;
}