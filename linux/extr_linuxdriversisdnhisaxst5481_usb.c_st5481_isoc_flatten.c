#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_iso_packet_descriptor {scalar_t__ status; unsigned int actual_length; int offset; } ;
struct urb {scalar_t__ status; size_t number_of_packets; unsigned char* transfer_buffer; struct usb_iso_packet_descriptor* iso_frame_desc; } ;

/* Variables and functions */

__attribute__((used)) static int st5481_isoc_flatten(struct urb *urb)
{
	struct usb_iso_packet_descriptor *pipd, *pend;
	unsigned char *src, *dst;
	unsigned int len;

	if (urb->status < 0) {
		return urb->status;
	}
	for (pipd = &urb->iso_frame_desc[0],
		     pend = &urb->iso_frame_desc[urb->number_of_packets],
		     dst = urb->transfer_buffer;
	     pipd < pend;
	     pipd++) {

		if (pipd->status < 0) {
			return (pipd->status);
		}

		len = pipd->actual_length;
		pipd->actual_length = 0;
		src = urb->transfer_buffer + pipd->offset;

		if (src != dst) {
			// Need to copy since isoc buffers not full
			while (len--) {
				*dst++ = *src++;
			}
		} else {
			// No need to copy, just update destination buffer
			dst += len;
		}
	}
	// Return size of flattened buffer
	return (dst - (unsigned char *)urb->transfer_buffer);
}