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
typedef  scalar_t__ u32 ;
struct dwc3_ep {int /*<<< orphan*/  name; } ;
struct dwc3 {struct dwc3_ep** eps; int /*<<< orphan*/  link_state; int /*<<< orphan*/  ep0state; int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; scalar_t__ imod_interval; } ;
struct TYPE_2__ {int /*<<< orphan*/  wMaxPacketSize; } ;

/* Variables and functions */
 scalar_t__ DWC31_GRXTHRCFG_PKTCNTSEL ; 
 int /*<<< orphan*/  DWC3_DEPCFG_ACTION_INIT ; 
 int /*<<< orphan*/  DWC3_DEV_IMOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GEVNTCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ DWC3_GEVNTCOUNT_EHB ; 
 int /*<<< orphan*/  DWC3_GRXTHRCFG ; 
 scalar_t__ DWC3_GRXTHRCFG_PKTCNTSEL ; 
 int /*<<< orphan*/  DWC3_LINK_STATE_SS_DIS ; 
 int /*<<< orphan*/  EP0_SETUP_PHASE ; 
 int /*<<< orphan*/  __dwc3_gadget_ep_disable (struct dwc3_ep*) ; 
 int __dwc3_gadget_ep_enable (struct dwc3_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_ep0_out_start (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_enable_irq (struct dwc3*) ; 
 TYPE_1__ dwc3_gadget_ep0_desc ; 
 int /*<<< orphan*/  dwc3_gadget_setup_nump (struct dwc3*) ; 
 scalar_t__ dwc3_has_imod (struct dwc3*) ; 
 scalar_t__ dwc3_is_usb31 (struct dwc3*) ; 
 scalar_t__ dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __dwc3_gadget_start(struct dwc3 *dwc)
{
	struct dwc3_ep		*dep;
	int			ret = 0;
	u32			reg;

	/*
	 * Use IMOD if enabled via dwc->imod_interval. Otherwise, if
	 * the core supports IMOD, disable it.
	 */
	if (dwc->imod_interval) {
		dwc3_writel(dwc->regs, DWC3_DEV_IMOD(0), dwc->imod_interval);
		dwc3_writel(dwc->regs, DWC3_GEVNTCOUNT(0), DWC3_GEVNTCOUNT_EHB);
	} else if (dwc3_has_imod(dwc)) {
		dwc3_writel(dwc->regs, DWC3_DEV_IMOD(0), 0);
	}

	/*
	 * We are telling dwc3 that we want to use DCFG.NUMP as ACK TP's NUMP
	 * field instead of letting dwc3 itself calculate that automatically.
	 *
	 * This way, we maximize the chances that we'll be able to get several
	 * bursts of data without going through any sort of endpoint throttling.
	 */
	reg = dwc3_readl(dwc->regs, DWC3_GRXTHRCFG);
	if (dwc3_is_usb31(dwc))
		reg &= ~DWC31_GRXTHRCFG_PKTCNTSEL;
	else
		reg &= ~DWC3_GRXTHRCFG_PKTCNTSEL;

	dwc3_writel(dwc->regs, DWC3_GRXTHRCFG, reg);

	dwc3_gadget_setup_nump(dwc);

	/* Start with SuperSpeed Default */
	dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);

	dep = dwc->eps[0];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_INIT);
	if (ret) {
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		goto err0;
	}

	dep = dwc->eps[1];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_INIT);
	if (ret) {
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		goto err1;
	}

	/* begin to receive SETUP packets */
	dwc->ep0state = EP0_SETUP_PHASE;
	dwc->link_state = DWC3_LINK_STATE_SS_DIS;
	dwc3_ep0_out_start(dwc);

	dwc3_gadget_enable_irq(dwc);

	return 0;

err1:
	__dwc3_gadget_ep_disable(dwc->eps[0]);

err0:
	return ret;
}