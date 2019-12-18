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
struct fotg210_qh_hw {int /*<<< orphan*/  hw_info2; int /*<<< orphan*/  hw_next; } ;
struct fotg210_qh {unsigned int start; unsigned int period; struct fotg210_qh_hw* hw; } ;
struct fotg210_hcd {unsigned int random_frame; } ;
typedef  int /*<<< orphan*/  __hc32 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  FOTG210_LIST_END (struct fotg210_hcd*) ; 
 int QH_CMASK ; 
 int QH_SMASK ; 
 int check_intr_schedule (struct fotg210_hcd*,unsigned int,unsigned int,struct fotg210_qh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_hc32 (struct fotg210_hcd*,int) ; 
 unsigned int ffs (int) ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,struct fotg210_qh*) ; 
 int hc32_to_cpup (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_link_periodic (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  qh_refresh (struct fotg210_hcd*,struct fotg210_qh*) ; 

__attribute__((used)) static int qh_schedule(struct fotg210_hcd *fotg210, struct fotg210_qh *qh)
{
	int status;
	unsigned uframe;
	__hc32 c_mask;
	unsigned frame;	/* 0..(qh->period - 1), or NO_FRAME */
	struct fotg210_qh_hw *hw = qh->hw;

	qh_refresh(fotg210, qh);
	hw->hw_next = FOTG210_LIST_END(fotg210);
	frame = qh->start;

	/* reuse the previous schedule slots, if we can */
	if (frame < qh->period) {
		uframe = ffs(hc32_to_cpup(fotg210, &hw->hw_info2) & QH_SMASK);
		status = check_intr_schedule(fotg210, frame, --uframe,
				qh, &c_mask);
	} else {
		uframe = 0;
		c_mask = 0;
		status = -ENOSPC;
	}

	/* else scan the schedule to find a group of slots such that all
	 * uframes have enough periodic bandwidth available.
	 */
	if (status) {
		/* "normal" case, uframing flexible except with splits */
		if (qh->period) {
			int i;

			for (i = qh->period; status && i > 0; --i) {
				frame = ++fotg210->random_frame % qh->period;
				for (uframe = 0; uframe < 8; uframe++) {
					status = check_intr_schedule(fotg210,
							frame, uframe, qh,
							&c_mask);
					if (status == 0)
						break;
				}
			}

		/* qh->period == 0 means every uframe */
		} else {
			frame = 0;
			status = check_intr_schedule(fotg210, 0, 0, qh,
					&c_mask);
		}
		if (status)
			goto done;
		qh->start = frame;

		/* reset S-frame and (maybe) C-frame masks */
		hw->hw_info2 &= cpu_to_hc32(fotg210, ~(QH_CMASK | QH_SMASK));
		hw->hw_info2 |= qh->period
			? cpu_to_hc32(fotg210, 1 << uframe)
			: cpu_to_hc32(fotg210, QH_SMASK);
		hw->hw_info2 |= c_mask;
	} else
		fotg210_dbg(fotg210, "reused qh %p schedule\n", qh);

	/* stuff into the periodic schedule */
	qh_link_periodic(fotg210, qh);
done:
	return status;
}