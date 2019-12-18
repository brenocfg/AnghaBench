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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct dwc2_hsotg_ep {int /*<<< orphan*/  desc_list_dma; scalar_t__ dir_in; int /*<<< orphan*/  index; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DIEPCTL (int /*<<< orphan*/ ) ; 
 int DIEPTSIZ (int /*<<< orphan*/ ) ; 
 int DOEPCTL (int /*<<< orphan*/ ) ; 
 int DOEPTSIZ (int /*<<< orphan*/ ) ; 
 int DXEPCTL_CNAK ; 
 int DXEPCTL_EPENA ; 
 int DXEPCTL_USBACTEP ; 
 int DXEPTSIZ_MC (int) ; 
 int DXEPTSIZ_PKTCNT (int) ; 
 int DXEPTSIZ_XFERSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_gadget_config_nonisoc_xfer_ddma (struct dwc2_hsotg_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_gadget_set_ep0_desc_chain (struct dwc2_hsotg*,struct dwc2_hsotg_ep*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int) ; 
 scalar_t__ using_desc_dma (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_hsotg_program_zlp(struct dwc2_hsotg *hsotg,
				   struct dwc2_hsotg_ep *hs_ep)
{
	u32 ctrl;
	u8 index = hs_ep->index;
	u32 epctl_reg = hs_ep->dir_in ? DIEPCTL(index) : DOEPCTL(index);
	u32 epsiz_reg = hs_ep->dir_in ? DIEPTSIZ(index) : DOEPTSIZ(index);

	if (hs_ep->dir_in)
		dev_dbg(hsotg->dev, "Sending zero-length packet on ep%d\n",
			index);
	else
		dev_dbg(hsotg->dev, "Receiving zero-length packet on ep%d\n",
			index);
	if (using_desc_dma(hsotg)) {
		/* Not specific buffer needed for ep0 ZLP */
		dma_addr_t dma = hs_ep->desc_list_dma;

		if (!index)
			dwc2_gadget_set_ep0_desc_chain(hsotg, hs_ep);

		dwc2_gadget_config_nonisoc_xfer_ddma(hs_ep, dma, 0);
	} else {
		dwc2_writel(hsotg, DXEPTSIZ_MC(1) | DXEPTSIZ_PKTCNT(1) |
			    DXEPTSIZ_XFERSIZE(0),
			    epsiz_reg);
	}

	ctrl = dwc2_readl(hsotg, epctl_reg);
	ctrl |= DXEPCTL_CNAK;  /* clear NAK set by core */
	ctrl |= DXEPCTL_EPENA; /* ensure ep enabled */
	ctrl |= DXEPCTL_USBACTEP;
	dwc2_writel(hsotg, ctrl, epctl_reg);
}