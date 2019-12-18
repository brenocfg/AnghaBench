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
struct usb_gadget {int dummy; } ;
struct dwc3 {scalar_t__ ep0state; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  ep0_in_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_PULL_UP_TIMEOUT ; 
 scalar_t__ EP0_SETUP_PHASE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc3_gadget_run_stop (struct dwc3*,int,int) ; 
 struct dwc3* gadget_to_dwc (struct usb_gadget*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_gadget_pullup(struct usb_gadget *g, int is_on)
{
	struct dwc3		*dwc = gadget_to_dwc(g);
	unsigned long		flags;
	int			ret;

	is_on = !!is_on;

	/*
	 * Per databook, when we want to stop the gadget, if a control transfer
	 * is still in process, complete it and get the core into setup phase.
	 */
	if (!is_on && dwc->ep0state != EP0_SETUP_PHASE) {
		reinit_completion(&dwc->ep0_in_setup);

		ret = wait_for_completion_timeout(&dwc->ep0_in_setup,
				msecs_to_jiffies(DWC3_PULL_UP_TIMEOUT));
		if (ret == 0) {
			dev_err(dwc->dev, "timed out waiting for SETUP phase\n");
			return -ETIMEDOUT;
		}
	}

	spin_lock_irqsave(&dwc->lock, flags);
	ret = dwc3_gadget_run_stop(dwc, is_on, false);
	spin_unlock_irqrestore(&dwc->lock, flags);

	return ret;
}