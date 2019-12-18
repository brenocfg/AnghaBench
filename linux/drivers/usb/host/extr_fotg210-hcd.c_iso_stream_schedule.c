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
typedef  unsigned int u32 ;
struct urb {unsigned int interval; unsigned int start_frame; struct fotg210_iso_sched* hcpriv; } ;
struct fotg210_iso_stream {unsigned int next_uframe; int /*<<< orphan*/  highspeed; int /*<<< orphan*/  usecs; int /*<<< orphan*/  td_list; } ;
struct fotg210_iso_sched {unsigned int span; } ;
struct fotg210_hcd {int periodic_size; unsigned int i_thresh; scalar_t__ isoc_count; unsigned int next_frame; scalar_t__ fs_i_thresh; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EFBIG ; 
 int ENOSPC ; 
 unsigned int SCHEDULE_SLOP ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,struct urb*,...) ; 
 unsigned int fotg210_read_frame_index (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  iso_sched_free (struct fotg210_iso_stream*,struct fotg210_iso_sched*) ; 
 scalar_t__ itd_slot_ok (struct fotg210_hcd*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int iso_stream_schedule(struct fotg210_hcd *fotg210, struct urb *urb,
		struct fotg210_iso_stream *stream)
{
	u32 now, next, start, period, span;
	int status;
	unsigned mod = fotg210->periodic_size << 3;
	struct fotg210_iso_sched *sched = urb->hcpriv;

	period = urb->interval;
	span = sched->span;

	if (span > mod - SCHEDULE_SLOP) {
		fotg210_dbg(fotg210, "iso request %p too long\n", urb);
		status = -EFBIG;
		goto fail;
	}

	now = fotg210_read_frame_index(fotg210) & (mod - 1);

	/* Typical case: reuse current schedule, stream is still active.
	 * Hopefully there are no gaps from the host falling behind
	 * (irq delays etc), but if there are we'll take the next
	 * slot in the schedule, implicitly assuming URB_ISO_ASAP.
	 */
	if (likely(!list_empty(&stream->td_list))) {
		u32 excess;

		/* For high speed devices, allow scheduling within the
		 * isochronous scheduling threshold.  For full speed devices
		 * and Intel PCI-based controllers, don't (work around for
		 * Intel ICH9 bug).
		 */
		if (!stream->highspeed && fotg210->fs_i_thresh)
			next = now + fotg210->i_thresh;
		else
			next = now;

		/* Fell behind (by up to twice the slop amount)?
		 * We decide based on the time of the last currently-scheduled
		 * slot, not the time of the next available slot.
		 */
		excess = (stream->next_uframe - period - next) & (mod - 1);
		if (excess >= mod - 2 * SCHEDULE_SLOP)
			start = next + excess - mod + period *
					DIV_ROUND_UP(mod - excess, period);
		else
			start = next + excess + period;
		if (start - now >= mod) {
			fotg210_dbg(fotg210, "request %p would overflow (%d+%d >= %d)\n",
					urb, start - now - period, period,
					mod);
			status = -EFBIG;
			goto fail;
		}
	}

	/* need to schedule; when's the next (u)frame we could start?
	 * this is bigger than fotg210->i_thresh allows; scheduling itself
	 * isn't free, the slop should handle reasonably slow cpus.  it
	 * can also help high bandwidth if the dma and irq loads don't
	 * jump until after the queue is primed.
	 */
	else {
		int done = 0;

		start = SCHEDULE_SLOP + (now & ~0x07);

		/* NOTE:  assumes URB_ISO_ASAP, to limit complexity/bugs */

		/* find a uframe slot with enough bandwidth.
		 * Early uframes are more precious because full-speed
		 * iso IN transfers can't use late uframes,
		 * and therefore they should be allocated last.
		 */
		next = start;
		start += period;
		do {
			start--;
			/* check schedule: enough space? */
			if (itd_slot_ok(fotg210, mod, start,
					stream->usecs, period))
				done = 1;
		} while (start > next && !done);

		/* no room in the schedule */
		if (!done) {
			fotg210_dbg(fotg210, "iso resched full %p (now %d max %d)\n",
					urb, now, now + mod);
			status = -ENOSPC;
			goto fail;
		}
	}

	/* Tried to schedule too far into the future? */
	if (unlikely(start - now + span - period >=
			mod - 2 * SCHEDULE_SLOP)) {
		fotg210_dbg(fotg210, "request %p would overflow (%d+%d >= %d)\n",
				urb, start - now, span - period,
				mod - 2 * SCHEDULE_SLOP);
		status = -EFBIG;
		goto fail;
	}

	stream->next_uframe = start & (mod - 1);

	/* report high speed start in uframes; full speed, in frames */
	urb->start_frame = stream->next_uframe;
	if (!stream->highspeed)
		urb->start_frame >>= 3;

	/* Make sure scan_isoc() sees these */
	if (fotg210->isoc_count == 0)
		fotg210->next_frame = now >> 3;
	return 0;

fail:
	iso_sched_free(stream, sched);
	urb->hcpriv = NULL;
	return status;
}