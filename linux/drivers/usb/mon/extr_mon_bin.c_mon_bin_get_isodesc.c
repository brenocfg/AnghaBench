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
struct usb_iso_packet_descriptor {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  status; } ;
struct urb {struct usb_iso_packet_descriptor* iso_frame_desc; } ;
struct mon_reader_bin {unsigned int b_size; TYPE_1__* b_vec; } ;
struct mon_bin_isodesc {scalar_t__ _pad; int /*<<< orphan*/  iso_len; int /*<<< orphan*/  iso_off; int /*<<< orphan*/  iso_status; } ;
struct TYPE_2__ {scalar_t__ ptr; } ;

/* Variables and functions */
 unsigned int CHUNK_SIZE ; 

__attribute__((used)) static void mon_bin_get_isodesc(const struct mon_reader_bin *rp,
    unsigned int offset, struct urb *urb, char ev_type, unsigned int ndesc)
{
	struct mon_bin_isodesc *dp;
	struct usb_iso_packet_descriptor *fp;

	fp = urb->iso_frame_desc;
	while (ndesc-- != 0) {
		dp = (struct mon_bin_isodesc *)
		    (rp->b_vec[offset / CHUNK_SIZE].ptr + offset % CHUNK_SIZE);
		dp->iso_status = fp->status;
		dp->iso_off = fp->offset;
		dp->iso_len = (ev_type == 'S') ? fp->length : fp->actual_length;
		dp->_pad = 0;
		if ((offset += sizeof(struct mon_bin_isodesc)) >= rp->b_size)
			offset = 0;
		fp++;
	}
}