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
struct qib_devdata {int /*<<< orphan*/  pioavail_lock; int /*<<< orphan*/  (* f_sendctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pio_need_disarm; } ;
struct qib_ctxtdata {unsigned int pio_base; unsigned int piocnt; unsigned int subctxt_cnt; int /*<<< orphan*/  ppd; int /*<<< orphan*/ * user_event_mask; struct qib_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_SENDCTRL_DISARM_BUF (unsigned int) ; 
 int /*<<< orphan*/  _QIB_EVENT_DISARM_BUFS_BIT ; 
 scalar_t__ __test_and_clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qib_disarm_piobufs_ifneeded(struct qib_ctxtdata *rcd)
{
	struct qib_devdata *dd = rcd->dd;
	unsigned i;
	unsigned last;
	unsigned n = 0;

	last = rcd->pio_base + rcd->piocnt;
	/*
	 * Don't need uctxt_lock here, since user has called in to us.
	 * Clear at start in case more interrupts set bits while we
	 * are disarming
	 */
	if (rcd->user_event_mask) {
		/*
		 * subctxt_cnt is 0 if not shared, so do base
		 * separately, first, then remaining subctxt, if any
		 */
		clear_bit(_QIB_EVENT_DISARM_BUFS_BIT, &rcd->user_event_mask[0]);
		for (i = 1; i < rcd->subctxt_cnt; i++)
			clear_bit(_QIB_EVENT_DISARM_BUFS_BIT,
				  &rcd->user_event_mask[i]);
	}
	spin_lock_irq(&dd->pioavail_lock);
	for (i = rcd->pio_base; i < last; i++) {
		if (__test_and_clear_bit(i, dd->pio_need_disarm)) {
			n++;
			dd->f_sendctrl(rcd->ppd, QIB_SENDCTRL_DISARM_BUF(i));
		}
	}
	spin_unlock_irq(&dd->pioavail_lock);
	return 0;
}