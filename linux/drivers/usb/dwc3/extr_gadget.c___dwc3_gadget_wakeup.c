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
typedef  int u8 ;
typedef  int u32 ;
struct dwc3 {scalar_t__ revision; int /*<<< orphan*/  dev; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_DCTL_ULSTCHNGREQ_MASK ; 
 int /*<<< orphan*/  DWC3_DSTS ; 
 int DWC3_DSTS_CONNECTSPD ; 
 int DWC3_DSTS_SUPERSPEED ; 
 int DWC3_DSTS_SUPERSPEED_PLUS ; 
 scalar_t__ DWC3_DSTS_USBLNKST (int) ; 
 int /*<<< orphan*/  DWC3_LINK_STATE_RECOV ; 
#define  DWC3_LINK_STATE_RX_DET 129 
 scalar_t__ DWC3_LINK_STATE_U0 ; 
#define  DWC3_LINK_STATE_U3 128 
 scalar_t__ DWC3_REVISION_194A ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc3_gadget_set_link_state (struct dwc3*,int /*<<< orphan*/ ) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __dwc3_gadget_wakeup(struct dwc3 *dwc)
{
	int			retries;

	int			ret;
	u32			reg;

	u8			link_state;
	u8			speed;

	/*
	 * According to the Databook Remote wakeup request should
	 * be issued only when the device is in early suspend state.
	 *
	 * We can check that via USB Link State bits in DSTS register.
	 */
	reg = dwc3_readl(dwc->regs, DWC3_DSTS);

	speed = reg & DWC3_DSTS_CONNECTSPD;
	if ((speed == DWC3_DSTS_SUPERSPEED) ||
	    (speed == DWC3_DSTS_SUPERSPEED_PLUS))
		return 0;

	link_state = DWC3_DSTS_USBLNKST(reg);

	switch (link_state) {
	case DWC3_LINK_STATE_RX_DET:	/* in HS, means Early Suspend */
	case DWC3_LINK_STATE_U3:	/* in HS, means SUSPEND */
		break;
	default:
		return -EINVAL;
	}

	ret = dwc3_gadget_set_link_state(dwc, DWC3_LINK_STATE_RECOV);
	if (ret < 0) {
		dev_err(dwc->dev, "failed to put link in Recovery\n");
		return ret;
	}

	/* Recent versions do this automatically */
	if (dwc->revision < DWC3_REVISION_194A) {
		/* write zeroes to Link Change Request */
		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		reg &= ~DWC3_DCTL_ULSTCHNGREQ_MASK;
		dwc3_writel(dwc->regs, DWC3_DCTL, reg);
	}

	/* poll until Link State changes to ON */
	retries = 20000;

	while (retries--) {
		reg = dwc3_readl(dwc->regs, DWC3_DSTS);

		/* in HS, means ON */
		if (DWC3_DSTS_USBLNKST(reg) == DWC3_LINK_STATE_U0)
			break;
	}

	if (DWC3_DSTS_USBLNKST(reg) != DWC3_LINK_STATE_U0) {
		dev_err(dwc->dev, "failed to send remote wakeup\n");
		return -EINVAL;
	}

	return 0;
}