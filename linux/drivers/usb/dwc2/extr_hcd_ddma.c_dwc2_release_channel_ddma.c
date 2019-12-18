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
struct dwc2_qh {scalar_t__ desc_list; scalar_t__ ntd; struct dwc2_host_chan* channel; } ;
struct TYPE_2__ {scalar_t__ uframe_sched; } ;
struct dwc2_hsotg {int /*<<< orphan*/  free_hc_list; int /*<<< orphan*/  available_host_channels; int /*<<< orphan*/  non_periodic_channels; TYPE_1__ params; } ;
struct dwc2_host_chan {int /*<<< orphan*/ * qh; int /*<<< orphan*/  hc_list_entry; } ;
struct dwc2_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_hc_cleanup (struct dwc2_hsotg*,struct dwc2_host_chan*) ; 
 int dwc2_max_desc_num (struct dwc2_qh*) ; 
 scalar_t__ dwc2_qh_is_non_per (struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_update_frame_list (struct dwc2_hsotg*,struct dwc2_qh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc2_release_channel_ddma(struct dwc2_hsotg *hsotg,
				      struct dwc2_qh *qh)
{
	struct dwc2_host_chan *chan = qh->channel;

	if (dwc2_qh_is_non_per(qh)) {
		if (hsotg->params.uframe_sched)
			hsotg->available_host_channels++;
		else
			hsotg->non_periodic_channels--;
	} else {
		dwc2_update_frame_list(hsotg, qh, 0);
		hsotg->available_host_channels++;
	}

	/*
	 * The condition is added to prevent double cleanup try in case of
	 * device disconnect. See channel cleanup in dwc2_hcd_disconnect().
	 */
	if (chan->qh) {
		if (!list_empty(&chan->hc_list_entry))
			list_del(&chan->hc_list_entry);
		dwc2_hc_cleanup(hsotg, chan);
		list_add_tail(&chan->hc_list_entry, &hsotg->free_hc_list);
		chan->qh = NULL;
	}

	qh->channel = NULL;
	qh->ntd = 0;

	if (qh->desc_list)
		memset(qh->desc_list, 0, sizeof(struct dwc2_dma_desc) *
		       dwc2_max_desc_num(qh));
}