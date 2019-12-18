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
typedef  size_t u32 ;
struct dwc2_hsotg_ep {int /*<<< orphan*/  isochronous; } ;
struct dwc2_hsotg {size_t num_of_eps; struct dwc2_hsotg_ep** eps_in; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int /*<<< orphan*/  DAINTMSK ; 
 int /*<<< orphan*/  DIEPCTL (size_t) ; 
 size_t DXEPCTL_EPDIS ; 
 size_t DXEPCTL_EPENA ; 
 size_t DXEPCTL_SNAK ; 
 int /*<<< orphan*/  GINTSTS ; 
 size_t GINTSTS_INCOMPL_SOIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dwc2_gadget_target_frame_elapsed (struct dwc2_hsotg_ep*) ; 
 size_t dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_gadget_handle_incomplete_isoc_in(struct dwc2_hsotg *hsotg)
{
	struct dwc2_hsotg_ep *hs_ep;
	u32 epctrl;
	u32 daintmsk;
	u32 idx;

	dev_dbg(hsotg->dev, "Incomplete isoc in interrupt received:\n");

	daintmsk = dwc2_readl(hsotg, DAINTMSK);

	for (idx = 1; idx < hsotg->num_of_eps; idx++) {
		hs_ep = hsotg->eps_in[idx];
		/* Proceed only unmasked ISOC EPs */
		if ((BIT(idx) & ~daintmsk) || !hs_ep->isochronous)
			continue;

		epctrl = dwc2_readl(hsotg, DIEPCTL(idx));
		if ((epctrl & DXEPCTL_EPENA) &&
		    dwc2_gadget_target_frame_elapsed(hs_ep)) {
			epctrl |= DXEPCTL_SNAK;
			epctrl |= DXEPCTL_EPDIS;
			dwc2_writel(hsotg, epctrl, DIEPCTL(idx));
		}
	}

	/* Clear interrupt */
	dwc2_writel(hsotg, GINTSTS_INCOMPL_SOIN, GINTSTS);
}