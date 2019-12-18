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
typedef  int u64 ;
typedef  int u32 ;
struct urb {int transfer_dma; int number_of_packets; int transfer_flags; TYPE_1__* iso_frame_desc; } ;
struct fotg210_iso_stream {int interval; } ;
struct fotg210_iso_sched {int span; struct fotg210_iso_packet* packet; } ;
struct fotg210_iso_packet {int bufp; int cross; int /*<<< orphan*/  transaction; } ;
struct fotg210_hcd {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {unsigned int length; int offset; } ;

/* Variables and functions */
 int FOTG210_ISOC_ACTIVE ; 
 int FOTG210_ITD_IOC ; 
 int URB_NO_INTERRUPT ; 
 int /*<<< orphan*/  cpu_to_hc32 (struct fotg210_hcd*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void itd_sched_init(struct fotg210_hcd *fotg210,
		struct fotg210_iso_sched *iso_sched,
		struct fotg210_iso_stream *stream, struct urb *urb)
{
	unsigned i;
	dma_addr_t dma = urb->transfer_dma;

	/* how many uframes are needed for these transfers */
	iso_sched->span = urb->number_of_packets * stream->interval;

	/* figure out per-uframe itd fields that we'll need later
	 * when we fit new itds into the schedule.
	 */
	for (i = 0; i < urb->number_of_packets; i++) {
		struct fotg210_iso_packet *uframe = &iso_sched->packet[i];
		unsigned length;
		dma_addr_t buf;
		u32 trans;

		length = urb->iso_frame_desc[i].length;
		buf = dma + urb->iso_frame_desc[i].offset;

		trans = FOTG210_ISOC_ACTIVE;
		trans |= buf & 0x0fff;
		if (unlikely(((i + 1) == urb->number_of_packets))
				&& !(urb->transfer_flags & URB_NO_INTERRUPT))
			trans |= FOTG210_ITD_IOC;
		trans |= length << 16;
		uframe->transaction = cpu_to_hc32(fotg210, trans);

		/* might need to cross a buffer page within a uframe */
		uframe->bufp = (buf & ~(u64)0x0fff);
		buf += length;
		if (unlikely((uframe->bufp != (buf & ~(u64)0x0fff))))
			uframe->cross = 1;
	}
}