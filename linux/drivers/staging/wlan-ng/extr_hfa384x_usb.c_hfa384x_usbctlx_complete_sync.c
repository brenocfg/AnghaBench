#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbctlx_completor {int (* complete ) (struct usbctlx_completor*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct hfa384x_usbctlx {int reapable; scalar_t__ state; int /*<<< orphan*/  list; TYPE_2__ outbuf; int /*<<< orphan*/  done; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  completing; } ;
struct hfa384x {int req_timer_done; int resp_timer_done; TYPE_3__ ctlxq; TYPE_1__* wlandev; int /*<<< orphan*/  ctlx_urb; int /*<<< orphan*/  resptimer; int /*<<< orphan*/  reqtimer; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; scalar_t__ hwremoved; } ;

/* Variables and functions */
 scalar_t__ CTLX_COMPLETE ; 
 scalar_t__ CTLX_REQ_FAILED ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  ctlxstr (scalar_t__) ; 
 int /*<<< orphan*/  del_singleshot_timer_sync (int /*<<< orphan*/ *) ; 
 struct hfa384x_usbctlx* get_active_ctlx (struct hfa384x*) ; 
 int /*<<< orphan*/  hfa384x_usbctlxq_run (struct hfa384x*) ; 
 int /*<<< orphan*/  kfree (struct hfa384x_usbctlx*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct usbctlx_completor*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfa384x_usbctlx_complete_sync(struct hfa384x *hw,
					 struct hfa384x_usbctlx *ctlx,
					 struct usbctlx_completor *completor)
{
	unsigned long flags;
	int result;

	result = wait_for_completion_interruptible(&ctlx->done);

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	/*
	 * We can only handle the CTLX if the USB disconnect
	 * function has not run yet ...
	 */
cleanup:
	if (hw->wlandev->hwremoved) {
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		result = -ENODEV;
	} else if (result != 0) {
		int runqueue = 0;

		/*
		 * We were probably interrupted, so delete
		 * this CTLX asynchronously, kill the timers
		 * and the URB, and then start the next
		 * pending CTLX.
		 *
		 * NOTE: We can only delete the timers and
		 *       the URB if this CTLX is active.
		 */
		if (ctlx == get_active_ctlx(hw)) {
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

			del_singleshot_timer_sync(&hw->reqtimer);
			del_singleshot_timer_sync(&hw->resptimer);
			hw->req_timer_done = 1;
			hw->resp_timer_done = 1;
			usb_kill_urb(&hw->ctlx_urb);

			spin_lock_irqsave(&hw->ctlxq.lock, flags);

			runqueue = 1;

			/*
			 * This scenario is so unlikely that I'm
			 * happy with a grubby "goto" solution ...
			 */
			if (hw->wlandev->hwremoved)
				goto cleanup;
		}

		/*
		 * The completion task will send this CTLX
		 * to the reaper the next time it runs. We
		 * are no longer in a hurry.
		 */
		ctlx->reapable = 1;
		ctlx->state = CTLX_REQ_FAILED;
		list_move_tail(&ctlx->list, &hw->ctlxq.completing);

		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

		if (runqueue)
			hfa384x_usbctlxq_run(hw);
	} else {
		if (ctlx->state == CTLX_COMPLETE) {
			result = completor->complete(completor);
		} else {
			netdev_warn(hw->wlandev->netdev, "CTLX[%d] error: state(%s)\n",
				    le16_to_cpu(ctlx->outbuf.type),
				    ctlxstr(ctlx->state));
			result = -EIO;
		}

		list_del(&ctlx->list);
		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
		kfree(ctlx);
	}

	return result;
}