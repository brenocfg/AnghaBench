#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_5__ {int maxpacket; } ;
struct dwc3_ep {int /*<<< orphan*/  name; TYPE_1__ endpoint; } ;
struct TYPE_7__ {TYPE_2__* ep0; int /*<<< orphan*/  speed; } ;
struct dwc3 {int speed; scalar_t__ revision; int hird_threshold; int is_utmi_l1_suspend; int /*<<< orphan*/  dev; struct dwc3_ep** eps; int /*<<< orphan*/  regs; int /*<<< orphan*/  lpm_nyet_threshold; scalar_t__ has_lpm_erratum; TYPE_3__ gadget; } ;
struct TYPE_8__ {void* wMaxPacketSize; } ;
struct TYPE_6__ {int maxpacket; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCFG ; 
 int DWC3_DCFG_LPM_CAP ; 
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_DCTL_HIRD_THRES (int) ; 
 int DWC3_DCTL_HIRD_THRES_MASK ; 
 int DWC3_DCTL_L1_HIBER_EN ; 
 int DWC3_DCTL_NYET_THRES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_DEPCFG_ACTION_MODIFY ; 
 int /*<<< orphan*/  DWC3_DSTS ; 
 int DWC3_DSTS_CONNECTSPD ; 
#define  DWC3_DSTS_FULLSPEED 132 
#define  DWC3_DSTS_HIGHSPEED 131 
#define  DWC3_DSTS_LOWSPEED 130 
#define  DWC3_DSTS_SUPERSPEED 129 
#define  DWC3_DSTS_SUPERSPEED_PLUS 128 
 scalar_t__ DWC3_REVISION_190A ; 
 scalar_t__ DWC3_REVISION_194A ; 
 scalar_t__ DWC3_REVISION_240A ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_LOW ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  USB_SPEED_SUPER_PLUS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int __dwc3_gadget_ep_enable (struct dwc3_ep*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__ dwc3_gadget_ep0_desc ; 
 int /*<<< orphan*/  dwc3_gadget_reset_interrupt (struct dwc3*) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_gadget_conndone_interrupt(struct dwc3 *dwc)
{
	struct dwc3_ep		*dep;
	int			ret;
	u32			reg;
	u8			speed;

	reg = dwc3_readl(dwc->regs, DWC3_DSTS);
	speed = reg & DWC3_DSTS_CONNECTSPD;
	dwc->speed = speed;

	/*
	 * RAMClkSel is reset to 0 after USB reset, so it must be reprogrammed
	 * each time on Connect Done.
	 *
	 * Currently we always use the reset value. If any platform
	 * wants to set this to a different value, we need to add a
	 * setting and update GCTL.RAMCLKSEL here.
	 */

	switch (speed) {
	case DWC3_DSTS_SUPERSPEED_PLUS:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);
		dwc->gadget.ep0->maxpacket = 512;
		dwc->gadget.speed = USB_SPEED_SUPER_PLUS;
		break;
	case DWC3_DSTS_SUPERSPEED:
		/*
		 * WORKAROUND: DWC3 revisions <1.90a have an issue which
		 * would cause a missing USB3 Reset event.
		 *
		 * In such situations, we should force a USB3 Reset
		 * event by calling our dwc3_gadget_reset_interrupt()
		 * routine.
		 *
		 * Refers to:
		 *
		 * STAR#9000483510: RTL: SS : USB3 reset event may
		 * not be generated always when the link enters poll
		 */
		if (dwc->revision < DWC3_REVISION_190A)
			dwc3_gadget_reset_interrupt(dwc);

		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);
		dwc->gadget.ep0->maxpacket = 512;
		dwc->gadget.speed = USB_SPEED_SUPER;
		break;
	case DWC3_DSTS_HIGHSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		dwc->gadget.ep0->maxpacket = 64;
		dwc->gadget.speed = USB_SPEED_HIGH;
		break;
	case DWC3_DSTS_FULLSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		dwc->gadget.ep0->maxpacket = 64;
		dwc->gadget.speed = USB_SPEED_FULL;
		break;
	case DWC3_DSTS_LOWSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(8);
		dwc->gadget.ep0->maxpacket = 8;
		dwc->gadget.speed = USB_SPEED_LOW;
		break;
	}

	dwc->eps[1]->endpoint.maxpacket = dwc->gadget.ep0->maxpacket;

	/* Enable USB2 LPM Capability */

	if ((dwc->revision > DWC3_REVISION_194A) &&
	    (speed != DWC3_DSTS_SUPERSPEED) &&
	    (speed != DWC3_DSTS_SUPERSPEED_PLUS)) {
		reg = dwc3_readl(dwc->regs, DWC3_DCFG);
		reg |= DWC3_DCFG_LPM_CAP;
		dwc3_writel(dwc->regs, DWC3_DCFG, reg);

		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		reg &= ~(DWC3_DCTL_HIRD_THRES_MASK | DWC3_DCTL_L1_HIBER_EN);

		reg |= DWC3_DCTL_HIRD_THRES(dwc->hird_threshold |
					    (dwc->is_utmi_l1_suspend << 4));

		/*
		 * When dwc3 revisions >= 2.40a, LPM Erratum is enabled and
		 * DCFG.LPMCap is set, core responses with an ACK and the
		 * BESL value in the LPM token is less than or equal to LPM
		 * NYET threshold.
		 */
		WARN_ONCE(dwc->revision < DWC3_REVISION_240A
				&& dwc->has_lpm_erratum,
				"LPM Erratum not available on dwc3 revisions < 2.40a\n");

		if (dwc->has_lpm_erratum && dwc->revision >= DWC3_REVISION_240A)
			reg |= DWC3_DCTL_NYET_THRES(dwc->lpm_nyet_threshold);

		dwc3_writel(dwc->regs, DWC3_DCTL, reg);
	} else {
		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		reg &= ~DWC3_DCTL_HIRD_THRES_MASK;
		dwc3_writel(dwc->regs, DWC3_DCTL, reg);
	}

	dep = dwc->eps[0];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_MODIFY);
	if (ret) {
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		return;
	}

	dep = dwc->eps[1];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_MODIFY);
	if (ret) {
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		return;
	}

	/*
	 * Configure PHY via GUSB3PIPECTLn if required.
	 *
	 * Update GTXFIFOSIZn
	 *
	 * In both cases reset values should be sufficient.
	 */
}