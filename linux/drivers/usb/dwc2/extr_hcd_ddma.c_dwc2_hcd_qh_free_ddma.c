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
struct dwc2_qh {scalar_t__ ep_type; scalar_t__ channel; } ;
struct TYPE_2__ {scalar_t__ uframe_sched; } ;
struct dwc2_hsotg {scalar_t__ frame_list; int /*<<< orphan*/  periodic_channels; TYPE_1__ params; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ USB_ENDPOINT_XFER_INT ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  dwc2_desc_list_free (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_frame_list_free (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_per_sched_disable (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_release_channel_ddma (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dwc2_hcd_qh_free_ddma(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	unsigned long flags;

	dwc2_desc_list_free(hsotg, qh);

	/*
	 * Channel still assigned due to some reasons.
	 * Seen on Isoc URB dequeue. Channel halted but no subsequent
	 * ChHalted interrupt to release the channel. Afterwards
	 * when it comes here from endpoint disable routine
	 * channel remains assigned.
	 */
	spin_lock_irqsave(&hsotg->lock, flags);
	if (qh->channel)
		dwc2_release_channel_ddma(hsotg, qh);
	spin_unlock_irqrestore(&hsotg->lock, flags);

	if ((qh->ep_type == USB_ENDPOINT_XFER_ISOC ||
	     qh->ep_type == USB_ENDPOINT_XFER_INT) &&
	    (hsotg->params.uframe_sched ||
	     !hsotg->periodic_channels) && hsotg->frame_list) {
		dwc2_per_sched_disable(hsotg);
		dwc2_frame_list_free(hsotg);
	}
}