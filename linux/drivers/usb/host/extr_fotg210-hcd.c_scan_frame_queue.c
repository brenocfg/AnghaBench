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
union fotg210_shadow {int /*<<< orphan*/ * ptr; TYPE_1__* itd; } ;
struct fotg210_hcd {scalar_t__ isoc_count; int /*<<< orphan*/ * periodic; union fotg210_shadow* pshadow; } ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_2__ {int* hw_transaction; int /*<<< orphan*/  hw_next; union fotg210_shadow itd_next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ITD_ACTIVE (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  Q_NEXT_TYPE (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 
#define  Q_TYPE_FSTN 130 
#define  Q_TYPE_ITD 129 
#define  Q_TYPE_QH 128 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int hc32_to_cpu (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 
 int itd_complete (struct fotg210_hcd*,TYPE_1__*) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline int scan_frame_queue(struct fotg210_hcd *fotg210, unsigned frame,
		unsigned now_frame, bool live)
{
	unsigned uf;
	bool modified;
	union fotg210_shadow q, *q_p;
	__hc32 type, *hw_p;

	/* scan each element in frame's queue for completions */
	q_p = &fotg210->pshadow[frame];
	hw_p = &fotg210->periodic[frame];
	q.ptr = q_p->ptr;
	type = Q_NEXT_TYPE(fotg210, *hw_p);
	modified = false;

	while (q.ptr) {
		switch (hc32_to_cpu(fotg210, type)) {
		case Q_TYPE_ITD:
			/* If this ITD is still active, leave it for
			 * later processing ... check the next entry.
			 * No need to check for activity unless the
			 * frame is current.
			 */
			if (frame == now_frame && live) {
				rmb();
				for (uf = 0; uf < 8; uf++) {
					if (q.itd->hw_transaction[uf] &
							ITD_ACTIVE(fotg210))
						break;
				}
				if (uf < 8) {
					q_p = &q.itd->itd_next;
					hw_p = &q.itd->hw_next;
					type = Q_NEXT_TYPE(fotg210,
							q.itd->hw_next);
					q = *q_p;
					break;
				}
			}

			/* Take finished ITDs out of the schedule
			 * and process them:  recycle, maybe report
			 * URB completion.  HC won't cache the
			 * pointer for much longer, if at all.
			 */
			*q_p = q.itd->itd_next;
			*hw_p = q.itd->hw_next;
			type = Q_NEXT_TYPE(fotg210, q.itd->hw_next);
			wmb();
			modified = itd_complete(fotg210, q.itd);
			q = *q_p;
			break;
		default:
			fotg210_dbg(fotg210, "corrupt type %d frame %d shadow %p\n",
					type, frame, q.ptr);
			/* FALL THROUGH */
		case Q_TYPE_QH:
		case Q_TYPE_FSTN:
			/* End of the iTDs and siTDs */
			q.ptr = NULL;
			break;
		}

		/* assume completion callbacks modify the queue */
		if (unlikely(modified && fotg210->isoc_count > 0))
			return -EINVAL;
	}
	return 0;
}