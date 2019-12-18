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
struct dwc2_qtd {int dummy; } ;
struct TYPE_2__ {scalar_t__ dma_desc_enable; } ;
struct dwc2_hsotg {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {scalar_t__ ep_type; } ;
typedef  enum dwc2_halt_status { ____Placeholder_dwc2_halt_status } dwc2_halt_status ;

/* Variables and functions */
 int DWC2_HC_XFER_BABBLE_ERR ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  HCINTMSK_BBLERR ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_hc_int (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_halt_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int) ; 
 int /*<<< orphan*/  dwc2_hc_handle_tt_clear (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*) ; 
 int /*<<< orphan*/  dwc2_hcd_complete_xfer_ddma (struct dwc2_hsotg*,struct dwc2_host_chan*,int,int) ; 
 int /*<<< orphan*/  dwc2_host_complete (struct dwc2_hsotg*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 
 int dwc2_update_isoc_urb_state (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*,int) ; 

__attribute__((used)) static void dwc2_hc_babble_intr(struct dwc2_hsotg *hsotg,
				struct dwc2_host_chan *chan, int chnum,
				struct dwc2_qtd *qtd)
{
	dev_dbg(hsotg->dev, "--Host Channel %d Interrupt: Babble Error--\n",
		chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	if (hsotg->params.dma_desc_enable) {
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFER_BABBLE_ERR);
		goto disable_int;
	}

	if (chan->ep_type != USB_ENDPOINT_XFER_ISOC) {
		dwc2_host_complete(hsotg, qtd, -EOVERFLOW);
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_BABBLE_ERR);
	} else {
		enum dwc2_halt_status halt_status;

		halt_status = dwc2_update_isoc_urb_state(hsotg, chan, chnum,
						qtd, DWC2_HC_XFER_BABBLE_ERR);
		dwc2_halt_channel(hsotg, chan, qtd, halt_status);
	}

disable_int:
	disable_hc_int(hsotg, chnum, HCINTMSK_BBLERR);
}