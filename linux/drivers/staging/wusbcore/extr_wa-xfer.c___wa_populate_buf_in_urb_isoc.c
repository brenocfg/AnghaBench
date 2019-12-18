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
struct wahc {int /*<<< orphan*/  dti_epd; } ;
struct wa_xfer {TYPE_1__* urb; } ;
struct wa_seg {int isoc_frame_index; int isoc_frame_count; int /*<<< orphan*/  isoc_frame_offset; } ;
struct usb_iso_packet_descriptor {int const actual_length; scalar_t__ offset; } ;
struct urb {scalar_t__ transfer_dma; int transfer_buffer_length; struct wa_seg* context; scalar_t__ num_sgs; int /*<<< orphan*/ * sg; int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/  transfer_flags; scalar_t__ num_mapped_sgs; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {scalar_t__ transfer_dma; struct usb_iso_packet_descriptor* iso_frame_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int usb_endpoint_maxp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __wa_populate_buf_in_urb_isoc(struct wahc *wa,
	struct urb *buf_in_urb, struct wa_xfer *xfer, struct wa_seg *seg)
{
	int urb_start_frame = seg->isoc_frame_index + seg->isoc_frame_offset;
	int seg_index, total_len = 0, urb_frame_index = urb_start_frame;
	struct usb_iso_packet_descriptor *iso_frame_desc =
						xfer->urb->iso_frame_desc;
	const int dti_packet_size = usb_endpoint_maxp(wa->dti_epd);
	int next_frame_contiguous;
	struct usb_iso_packet_descriptor *iso_frame;

	BUG_ON(buf_in_urb->status == -EINPROGRESS);

	/*
	 * If the current frame actual_length is contiguous with the next frame
	 * and actual_length is a multiple of the DTI endpoint max packet size,
	 * combine the current frame with the next frame in a single URB.  This
	 * reduces the number of URBs that must be submitted in that case.
	 */
	seg_index = seg->isoc_frame_index;
	do {
		next_frame_contiguous = 0;

		iso_frame = &iso_frame_desc[urb_frame_index];
		total_len += iso_frame->actual_length;
		++urb_frame_index;
		++seg_index;

		if (seg_index < seg->isoc_frame_count) {
			struct usb_iso_packet_descriptor *next_iso_frame;

			next_iso_frame = &iso_frame_desc[urb_frame_index];

			if ((iso_frame->offset + iso_frame->actual_length) ==
				next_iso_frame->offset)
				next_frame_contiguous = 1;
		}
	} while (next_frame_contiguous
			&& ((iso_frame->actual_length % dti_packet_size) == 0));

	/* this should always be 0 before a resubmit. */
	buf_in_urb->num_mapped_sgs	= 0;
	buf_in_urb->transfer_dma = xfer->urb->transfer_dma +
		iso_frame_desc[urb_start_frame].offset;
	buf_in_urb->transfer_buffer_length = total_len;
	buf_in_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	buf_in_urb->transfer_buffer = NULL;
	buf_in_urb->sg = NULL;
	buf_in_urb->num_sgs = 0;
	buf_in_urb->context = seg;

	/* return the number of frames included in this URB. */
	return seg_index - seg->isoc_frame_index;
}