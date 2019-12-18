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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_event_depevt {int status; } ;
struct dwc3_ep {int flags; int /*<<< orphan*/  started_list; struct dwc3* dwc; } ;
struct dwc3 {scalar_t__ revision; int /*<<< orphan*/  u1u2; int /*<<< orphan*/  regs; struct dwc3_ep** eps; } ;

/* Variables and functions */
 int DEPEVT_STATUS_BUSERR ; 
 int DEPEVT_STATUS_MISSED_ISOC ; 
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_ENDPOINTS_NUM ; 
 int DWC3_EP_ENABLED ; 
 scalar_t__ DWC3_REVISION_183A ; 
 unsigned int ECONNRESET ; 
 unsigned int EXDEV ; 
 int /*<<< orphan*/  dwc3_gadget_endpoint_frame_from_event (struct dwc3_ep*,struct dwc3_event_depevt const*) ; 
 int /*<<< orphan*/  dwc3_gadget_ep_cleanup_completed_requests (struct dwc3_ep*,struct dwc3_event_depevt const*,unsigned int) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_stop_active_transfer (struct dwc3_ep*,int,int) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc3_gadget_endpoint_transfer_in_progress(struct dwc3_ep *dep,
		const struct dwc3_event_depevt *event)
{
	struct dwc3		*dwc = dep->dwc;
	unsigned		status = 0;
	bool			stop = false;

	dwc3_gadget_endpoint_frame_from_event(dep, event);

	if (event->status & DEPEVT_STATUS_BUSERR)
		status = -ECONNRESET;

	if (event->status & DEPEVT_STATUS_MISSED_ISOC) {
		status = -EXDEV;

		if (list_empty(&dep->started_list))
			stop = true;
	}

	dwc3_gadget_ep_cleanup_completed_requests(dep, event, status);

	if (stop) {
		dwc3_stop_active_transfer(dep, true, true);
		dep->flags = DWC3_EP_ENABLED;
	}

	/*
	 * WORKAROUND: This is the 2nd half of U1/U2 -> U0 workaround.
	 * See dwc3_gadget_linksts_change_interrupt() for 1st half.
	 */
	if (dwc->revision < DWC3_REVISION_183A) {
		u32		reg;
		int		i;

		for (i = 0; i < DWC3_ENDPOINTS_NUM; i++) {
			dep = dwc->eps[i];

			if (!(dep->flags & DWC3_EP_ENABLED))
				continue;

			if (!list_empty(&dep->started_list))
				return;
		}

		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		reg |= dwc->u1u2;
		dwc3_writel(dwc->regs, DWC3_DCTL, reg);

		dwc->u1u2 = 0;
	}
}