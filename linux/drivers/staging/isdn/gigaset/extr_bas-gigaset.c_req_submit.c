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
struct bc_state {TYPE_3__* cs; } ;
struct TYPE_5__ {int bRequest; scalar_t__ wLength; scalar_t__ wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequestType; } ;
struct bas_cardstate {int pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer_ctrl; int /*<<< orphan*/  urb_ctrl; scalar_t__ retry_ctrl; TYPE_2__ dr_ctrl; int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {struct bas_cardstate* bas; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_USBREQ ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  OUT_VENDOR_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int get_usb_rcmsg (int) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_fill_control_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bas_cardstate*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ctrl_callback ; 

__attribute__((used)) static int req_submit(struct bc_state *bcs, int req, int val, int timeout)
{
	struct bas_cardstate *ucs = bcs->cs->hw.bas;
	int ret;
	unsigned long flags;

	gig_dbg(DEBUG_USBREQ, "-------> 0x%02x (%d)", req, val);

	spin_lock_irqsave(&ucs->lock, flags);
	if (ucs->pending) {
		spin_unlock_irqrestore(&ucs->lock, flags);
		dev_err(bcs->cs->dev,
			"submission of request 0x%02x failed: "
			"request 0x%02x still pending\n",
			req, ucs->pending);
		return -EBUSY;
	}

	ucs->dr_ctrl.bRequestType = OUT_VENDOR_REQ;
	ucs->dr_ctrl.bRequest = req;
	ucs->dr_ctrl.wValue = cpu_to_le16(val);
	ucs->dr_ctrl.wIndex = 0;
	ucs->dr_ctrl.wLength = 0;
	usb_fill_control_urb(ucs->urb_ctrl, ucs->udev,
			     usb_sndctrlpipe(ucs->udev, 0),
			     (unsigned char *) &ucs->dr_ctrl, NULL, 0,
			     write_ctrl_callback, ucs);
	ucs->retry_ctrl = 0;
	ret = usb_submit_urb(ucs->urb_ctrl, GFP_ATOMIC);
	if (unlikely(ret)) {
		dev_err(bcs->cs->dev, "could not submit request 0x%02x: %s\n",
			req, get_usb_rcmsg(ret));
		spin_unlock_irqrestore(&ucs->lock, flags);
		return ret;
	}
	ucs->pending = req;

	if (timeout > 0) {
		gig_dbg(DEBUG_USBREQ, "setting timeout of %d/10 secs", timeout);
		mod_timer(&ucs->timer_ctrl, jiffies + timeout * HZ / 10);
	}

	spin_unlock_irqrestore(&ucs->lock, flags);
	return 0;
}