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
struct usb_iso_packet_descriptor {unsigned int actual_length; unsigned int offset; } ;
struct urb {struct usb_iso_packet_descriptor* iso_frame_desc; } ;
struct mon_reader_bin {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int mon_bin_collate_isodesc(const struct mon_reader_bin *rp,
    struct urb *urb, unsigned int ndesc)
{
	struct usb_iso_packet_descriptor *fp;
	unsigned int length;

	length = 0;
	fp = urb->iso_frame_desc;
	while (ndesc-- != 0) {
		if (fp->actual_length != 0) {
			if (fp->offset + fp->actual_length > length)
				length = fp->offset + fp->actual_length;
		}
		fp++;
	}
	return length;
}