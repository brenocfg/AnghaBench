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
typedef  int /*<<< orphan*/  u32 ;
struct dwc2_hsotg_ep {int dir_in; int target_frame; int interval; int /*<<< orphan*/  index; int /*<<< orphan*/  isochronous; struct dwc2_hsotg* parent; } ;
struct TYPE_2__ {scalar_t__ service_interval; } ;
struct dwc2_hsotg {int frame_number; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIEPCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DXEPCTL_SETEVENFR ; 
 int /*<<< orphan*/  DXEPCTL_SETODDFR ; 
 int TARGET_FRAME_INITIAL ; 
 int /*<<< orphan*/  dwc2_gadget_dec_frame_num_by_one (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  dwc2_gadget_incr_frame_num (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  dwc2_gadget_start_isoc_ddma (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  dwc2_hsotg_complete_request (struct dwc2_hsotg*,struct dwc2_hsotg_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ep_head (struct dwc2_hsotg_ep*) ; 
 scalar_t__ using_desc_dma (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_gadget_handle_nak(struct dwc2_hsotg_ep *hs_ep)
{
	struct dwc2_hsotg *hsotg = hs_ep->parent;
	int dir_in = hs_ep->dir_in;

	if (!dir_in || !hs_ep->isochronous)
		return;

	if (hs_ep->target_frame == TARGET_FRAME_INITIAL) {

		if (using_desc_dma(hsotg)) {
			hs_ep->target_frame = hsotg->frame_number;
			dwc2_gadget_incr_frame_num(hs_ep);

			/* In service interval mode target_frame must
			 * be set to last (u)frame of the service interval.
			 */
			if (hsotg->params.service_interval) {
				/* Set target_frame to the first (u)frame of
				 * the service interval
				 */
				hs_ep->target_frame &= ~hs_ep->interval + 1;

				/* Set target_frame to the last (u)frame of
				 * the service interval
				 */
				dwc2_gadget_incr_frame_num(hs_ep);
				dwc2_gadget_dec_frame_num_by_one(hs_ep);
			}

			dwc2_gadget_start_isoc_ddma(hs_ep);
			return;
		}

		hs_ep->target_frame = hsotg->frame_number;
		if (hs_ep->interval > 1) {
			u32 ctrl = dwc2_readl(hsotg,
					      DIEPCTL(hs_ep->index));
			if (hs_ep->target_frame & 0x1)
				ctrl |= DXEPCTL_SETODDFR;
			else
				ctrl |= DXEPCTL_SETEVENFR;

			dwc2_writel(hsotg, ctrl, DIEPCTL(hs_ep->index));
		}

		dwc2_hsotg_complete_request(hsotg, hs_ep,
					    get_ep_head(hs_ep), 0);
	}

	if (!using_desc_dma(hsotg))
		dwc2_gadget_incr_frame_num(hs_ep);
}