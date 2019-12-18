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
struct hfa384x_usbctlx {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_flags; } ;
struct hfa384x {TYPE_1__ ctlx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLX_REQ_FAILED ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  URB_ASYNC_UNLINK ; 
 int /*<<< orphan*/  unlocked_usbctlx_complete (struct hfa384x*,struct hfa384x_usbctlx*) ; 
 int usb_unlink_urb (TYPE_1__*) ; 

__attribute__((used)) static int unlocked_usbctlx_cancel_async(struct hfa384x *hw,
					 struct hfa384x_usbctlx *ctlx)
{
	int ret;

	/*
	 * Try to delete the URB containing our request packet.
	 * If we succeed, then its completion handler will be
	 * called with a status of -ECONNRESET.
	 */
	hw->ctlx_urb.transfer_flags |= URB_ASYNC_UNLINK;
	ret = usb_unlink_urb(&hw->ctlx_urb);

	if (ret != -EINPROGRESS) {
		/*
		 * The OUT URB had either already completed
		 * or was still in the pending queue, so the
		 * URB's completion function will not be called.
		 * We will have to complete the CTLX ourselves.
		 */
		ctlx->state = CTLX_REQ_FAILED;
		unlocked_usbctlx_complete(hw, ctlx);
		ret = 0;
	}

	return ret;
}