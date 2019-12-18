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
struct qib_ctxtdata {int subctxt_cnt; int /*<<< orphan*/  ppd; int /*<<< orphan*/ * user_event_mask; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  _QIB_EVENT_DISARM_BUFS_BIT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disarm_req_delay(struct qib_ctxtdata *rcd)
{
	int ret = 0;

	if (!usable(rcd->ppd)) {
		int i;
		/*
		 * if link is down, or otherwise not usable, delay
		 * the caller up to 30 seconds, so we don't thrash
		 * in trying to get the chip back to ACTIVE, and
		 * set flag so they make the call again.
		 */
		if (rcd->user_event_mask) {
			/*
			 * subctxt_cnt is 0 if not shared, so do base
			 * separately, first, then remaining subctxt, if any
			 */
			set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
				&rcd->user_event_mask[0]);
			for (i = 1; i < rcd->subctxt_cnt; i++)
				set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
					&rcd->user_event_mask[i]);
		}
		for (i = 0; !usable(rcd->ppd) && i < 300; i++)
			msleep(100);
		ret = -ENETDOWN;
	}
	return ret;
}