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
struct hfi1_devdata {int /*<<< orphan*/  uctxt_lock; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  wait; int /*<<< orphan*/  urgent; int /*<<< orphan*/  event_flags; int /*<<< orphan*/  in_use_ctxts; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_CTXT_WAITING_RCV ; 
 int /*<<< orphan*/  HFI1_CTXT_WAITING_URG ; 
 int /*<<< orphan*/  HFI1_MAX_SHARED_CTXTS ; 
 int /*<<< orphan*/  HFI1_RCVCTRL_INTRAVAIL_DIS ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void handle_user_interrupt(struct hfi1_ctxtdata *rcd)
{
	struct hfi1_devdata *dd = rcd->dd;
	unsigned long flags;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	if (bitmap_empty(rcd->in_use_ctxts, HFI1_MAX_SHARED_CTXTS))
		goto done;

	if (test_and_clear_bit(HFI1_CTXT_WAITING_RCV, &rcd->event_flags)) {
		wake_up_interruptible(&rcd->wait);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_INTRAVAIL_DIS, rcd);
	} else if (test_and_clear_bit(HFI1_CTXT_WAITING_URG,
							&rcd->event_flags)) {
		rcd->urgent++;
		wake_up_interruptible(&rcd->wait);
	}
done:
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
}