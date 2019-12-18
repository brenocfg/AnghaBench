#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  status; struct hfa384x* context; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct hfa384x_usbctlx {int state; TYPE_1__ outbuf; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;
struct hfa384x {int req_timer_done; int resp_timer_done; TYPE_3__ ctlxq; int /*<<< orphan*/  resptimer; int /*<<< orphan*/  usb_work; TYPE_2__* wlandev; int /*<<< orphan*/  usb_flags; int /*<<< orphan*/  reqtimer; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__* netdev; } ;

/* Variables and functions */
 int CTLX_COMPLETE ; 
 int CTLX_REQ_COMPLETE ; 
 int CTLX_REQ_FAILED ; 
#define  CTLX_REQ_SUBMITTED 129 
#define  CTLX_RESP_COMPLETE 128 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  WORK_TX_HALT ; 
 int /*<<< orphan*/  ctlxstr (int) ; 
 int /*<<< orphan*/  dbprint_urb (struct urb*) ; 
 int del_timer (int /*<<< orphan*/ *) ; 
 struct hfa384x_usbctlx* get_active_ctlx (struct hfa384x*) ; 
 int /*<<< orphan*/  hfa384x_usbctlxq_run (struct hfa384x*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlocked_usbctlx_complete (struct hfa384x*,struct hfa384x_usbctlx*) ; 

__attribute__((used)) static void hfa384x_ctlxout_callback(struct urb *urb)
{
	struct hfa384x *hw = urb->context;
	int delete_resptimer = 0;
	int timer_ok = 1;
	int run_queue = 0;
	struct hfa384x_usbctlx *ctlx;
	unsigned long flags;

	pr_debug("urb->status=%d\n", urb->status);
#ifdef DEBUG_USB
	dbprint_urb(urb);
#endif
	if ((urb->status == -ESHUTDOWN) ||
	    (urb->status == -ENODEV) || !hw)
		return;

retry:
	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/*
	 * Only one CTLX at a time on the "active" list, and
	 * none at all if we are unplugged. However, we can
	 * rely on the disconnect function to clean everything
	 * up if someone unplugged the adapter.
	 */
	if (list_empty(&hw->ctlxq.active)) {
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		return;
	}

	/*
	 * Having something on the "active" queue means
	 * that we have timers to worry about ...
	 */
	if (del_timer(&hw->reqtimer) == 0) {
		if (hw->req_timer_done == 0) {
			/*
			 * This timer was actually running while we
			 * were trying to delete it. Let it terminate
			 * gracefully instead.
			 */
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			goto retry;
		}
	} else {
		hw->req_timer_done = 1;
	}

	ctlx = get_active_ctlx(hw);

	if (urb->status == 0) {
		/* Request portion of a CTLX is successful */
		switch (ctlx->state) {
		case CTLX_REQ_SUBMITTED:
			/* This OUT-ACK received before IN */
			ctlx->state = CTLX_REQ_COMPLETE;
			break;

		case CTLX_RESP_COMPLETE:
			/* IN already received before this OUT-ACK,
			 * so this command must now be complete.
			 */
			ctlx->state = CTLX_COMPLETE;
			unlocked_usbctlx_complete(hw, ctlx);
			run_queue = 1;
			break;

		default:
			/* This is NOT a valid CTLX "success" state! */
			netdev_err(hw->wlandev->netdev,
				   "Illegal CTLX[%d] success state(%s, %d) in OUT URB\n",
				   le16_to_cpu(ctlx->outbuf.type),
				   ctlxstr(ctlx->state), urb->status);
			break;
		}		/* switch */
	} else {
		/* If the pipe has stalled then we need to reset it */
		if ((urb->status == -EPIPE) &&
		    !test_and_set_bit(WORK_TX_HALT, &hw->usb_flags)) {
			netdev_warn(hw->wlandev->netdev,
				    "%s tx pipe stalled: requesting reset\n",
				    hw->wlandev->netdev->name);
			schedule_work(&hw->usb_work);
		}

		/* If someone cancels the OUT URB then its status
		 * should be either -ECONNRESET or -ENOENT.
		 */
		ctlx->state = CTLX_REQ_FAILED;
		unlocked_usbctlx_complete(hw, ctlx);
		delete_resptimer = 1;
		run_queue = 1;
	}

delresp:
	if (delete_resptimer) {
		timer_ok = del_timer(&hw->resptimer);
		if (timer_ok != 0)
			hw->resp_timer_done = 1;
	}

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

	if (!timer_ok && (hw->resp_timer_done == 0)) {
		spin_lock_irqsave(&hw->ctlxq.lock, flags);
		goto delresp;
	}

	if (run_queue)
		hfa384x_usbctlxq_run(hw);
}