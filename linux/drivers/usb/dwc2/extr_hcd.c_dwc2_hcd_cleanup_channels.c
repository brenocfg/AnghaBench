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
typedef  int u32 ;
struct TYPE_2__ {int host_channels; scalar_t__ uframe_sched; int /*<<< orphan*/  host_dma; } ;
struct dwc2_hsotg {int available_host_channels; scalar_t__ periodic_channels; scalar_t__ non_periodic_channels; TYPE_1__ params; int /*<<< orphan*/  free_hc_list; struct dwc2_host_chan** hc_ptr_array; } ;
struct dwc2_host_chan {int /*<<< orphan*/ * qh; int /*<<< orphan*/  hc_list_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCCHAR (int) ; 
 int HCCHAR_CHDIS ; 
 int HCCHAR_CHENA ; 
 int HCCHAR_EPDIR ; 
 int /*<<< orphan*/  dwc2_hc_cleanup (struct dwc2_hsotg*,struct dwc2_host_chan*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc2_hcd_cleanup_channels(struct dwc2_hsotg *hsotg)
{
	int num_channels = hsotg->params.host_channels;
	struct dwc2_host_chan *channel;
	u32 hcchar;
	int i;

	if (!hsotg->params.host_dma) {
		/* Flush out any channel requests in slave mode */
		for (i = 0; i < num_channels; i++) {
			channel = hsotg->hc_ptr_array[i];
			if (!list_empty(&channel->hc_list_entry))
				continue;
			hcchar = dwc2_readl(hsotg, HCCHAR(i));
			if (hcchar & HCCHAR_CHENA) {
				hcchar &= ~(HCCHAR_CHENA | HCCHAR_EPDIR);
				hcchar |= HCCHAR_CHDIS;
				dwc2_writel(hsotg, hcchar, HCCHAR(i));
			}
		}
	}

	for (i = 0; i < num_channels; i++) {
		channel = hsotg->hc_ptr_array[i];
		if (!list_empty(&channel->hc_list_entry))
			continue;
		hcchar = dwc2_readl(hsotg, HCCHAR(i));
		if (hcchar & HCCHAR_CHENA) {
			/* Halt the channel */
			hcchar |= HCCHAR_CHDIS;
			dwc2_writel(hsotg, hcchar, HCCHAR(i));
		}

		dwc2_hc_cleanup(hsotg, channel);
		list_add_tail(&channel->hc_list_entry, &hsotg->free_hc_list);
		/*
		 * Added for Descriptor DMA to prevent channel double cleanup in
		 * release_channel_ddma(), which is called from ep_disable when
		 * device disconnects
		 */
		channel->qh = NULL;
	}
	/* All channels have been freed, mark them available */
	if (hsotg->params.uframe_sched) {
		hsotg->available_host_channels =
			hsotg->params.host_channels;
	} else {
		hsotg->non_periodic_channels = 0;
		hsotg->periodic_channels = 0;
	}
}