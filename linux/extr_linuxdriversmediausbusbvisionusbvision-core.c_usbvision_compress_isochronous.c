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
struct usb_usbvision {scalar_t__ isocstate; int isoc_packet_size; int isoc_data_count; int /*<<< orphan*/  isoc_packet_count; int /*<<< orphan*/  scratch_ovf_count; int /*<<< orphan*/  isoc_skip_count; int /*<<< orphan*/  isoc_err_count; } ;
struct urb {int number_of_packets; unsigned char* transfer_buffer; TYPE_1__* iso_frame_desc; } ;
struct TYPE_2__ {int actual_length; int status; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ISOC ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isoc_state_in_frame ; 
 scalar_t__ isoc_state_no_frame ; 
 int scratch_free (struct usb_usbvision*) ; 
 int scratch_len (struct usb_usbvision*) ; 
 int /*<<< orphan*/  scratch_mark_header (struct usb_usbvision*) ; 
 int /*<<< orphan*/  scratch_put (struct usb_usbvision*,unsigned char*,int) ; 
 int /*<<< orphan*/  scratch_rm_old (struct usb_usbvision*,int) ; 
 int /*<<< orphan*/  usbvision_measure_bandwidth (struct usb_usbvision*) ; 

__attribute__((used)) static int usbvision_compress_isochronous(struct usb_usbvision *usbvision,
					  struct urb *urb)
{
	unsigned char *packet_data;
	int i, totlen = 0;

	for (i = 0; i < urb->number_of_packets; i++) {
		int packet_len = urb->iso_frame_desc[i].actual_length;
		int packet_stat = urb->iso_frame_desc[i].status;

		packet_data = urb->transfer_buffer + urb->iso_frame_desc[i].offset;

		/* Detect and ignore errored packets */
		if (packet_stat) {	/* packet_stat != 0 ????????????? */
			PDEBUG(DBG_ISOC, "data error: [%d] len=%d, status=%X", i, packet_len, packet_stat);
			usbvision->isoc_err_count++;
			continue;
		}

		/* Detect and ignore empty packets */
		if (packet_len < 0) {
			PDEBUG(DBG_ISOC, "error packet [%d]", i);
			usbvision->isoc_skip_count++;
			continue;
		} else if (packet_len == 0) {	/* Frame end ????? */
			PDEBUG(DBG_ISOC, "null packet [%d]", i);
			usbvision->isocstate = isoc_state_no_frame;
			usbvision->isoc_skip_count++;
			continue;
		} else if (packet_len > usbvision->isoc_packet_size) {
			PDEBUG(DBG_ISOC, "packet[%d] > isoc_packet_size", i);
			usbvision->isoc_skip_count++;
			continue;
		}

		PDEBUG(DBG_ISOC, "packet ok [%d] len=%d", i, packet_len);

		if (usbvision->isocstate == isoc_state_no_frame) { /* new frame begins */
			usbvision->isocstate = isoc_state_in_frame;
			scratch_mark_header(usbvision);
			usbvision_measure_bandwidth(usbvision);
			PDEBUG(DBG_ISOC, "packet with header");
		}

		/*
		 * If usbvision continues to feed us with data but there is no
		 * consumption (if, for example, V4L client fell asleep) we
		 * may overflow the buffer. We have to move old data over to
		 * free room for new data. This is bad for old data. If we
		 * just drop new data then it's bad for new data... choose
		 * your favorite evil here.
		 */
		if (scratch_free(usbvision) < packet_len) {
			usbvision->scratch_ovf_count++;
			PDEBUG(DBG_ISOC, "scratch buf overflow! scr_len: %d, n: %d",
			       scratch_len(usbvision), packet_len);
			scratch_rm_old(usbvision, packet_len - scratch_free(usbvision));
		}

		/* Now we know that there is enough room in scratch buffer */
		scratch_put(usbvision, packet_data, packet_len);
		totlen += packet_len;
		usbvision->isoc_data_count += packet_len;
		usbvision->isoc_packet_count++;
	}
#if ENABLE_HEXDUMP
	if (totlen > 0) {
		static int foo;

		if (foo < 1) {
			printk(KERN_DEBUG "+%d.\n", usbvision->scratchlen);
			usbvision_hexdump(data0, (totlen > 64) ? 64 : totlen);
			++foo;
		}
	}
#endif
	return totlen;
}