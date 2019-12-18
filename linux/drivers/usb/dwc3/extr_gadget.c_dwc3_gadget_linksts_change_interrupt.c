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
struct TYPE_2__ {int /*<<< orphan*/  hwparams1; } ;
struct dwc3 {scalar_t__ revision; int link_state; int u1u2; int /*<<< orphan*/  speed; int /*<<< orphan*/  regs; TYPE_1__ hwparams; } ;
typedef  enum dwc3_link_state { ____Placeholder_dwc3_link_state } dwc3_link_state ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_DCTL_ACCEPTU1ENA ; 
 int DWC3_DCTL_ACCEPTU2ENA ; 
 int DWC3_DCTL_INITU1ENA ; 
 int DWC3_DCTL_INITU2ENA ; 
 unsigned int DWC3_GHWPARAMS1_EN_PWROPT (int /*<<< orphan*/ ) ; 
 unsigned int DWC3_GHWPARAMS1_EN_PWROPT_HIB ; 
 unsigned int DWC3_LINK_STATE_MASK ; 
#define  DWC3_LINK_STATE_RESUME 131 
 int DWC3_LINK_STATE_U0 ; 
#define  DWC3_LINK_STATE_U1 130 
#define  DWC3_LINK_STATE_U2 129 
#define  DWC3_LINK_STATE_U3 128 
 scalar_t__ DWC3_REVISION_183A ; 
 scalar_t__ DWC3_REVISION_250A ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_resume_gadget (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_suspend_gadget (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_gadget_linksts_change_interrupt(struct dwc3 *dwc,
		unsigned int evtinfo)
{
	enum dwc3_link_state	next = evtinfo & DWC3_LINK_STATE_MASK;
	unsigned int		pwropt;

	/*
	 * WORKAROUND: DWC3 < 2.50a have an issue when configured without
	 * Hibernation mode enabled which would show up when device detects
	 * host-initiated U3 exit.
	 *
	 * In that case, device will generate a Link State Change Interrupt
	 * from U3 to RESUME which is only necessary if Hibernation is
	 * configured in.
	 *
	 * There are no functional changes due to such spurious event and we
	 * just need to ignore it.
	 *
	 * Refers to:
	 *
	 * STAR#9000570034 RTL: SS Resume event generated in non-Hibernation
	 * operational mode
	 */
	pwropt = DWC3_GHWPARAMS1_EN_PWROPT(dwc->hwparams.hwparams1);
	if ((dwc->revision < DWC3_REVISION_250A) &&
			(pwropt != DWC3_GHWPARAMS1_EN_PWROPT_HIB)) {
		if ((dwc->link_state == DWC3_LINK_STATE_U3) &&
				(next == DWC3_LINK_STATE_RESUME)) {
			return;
		}
	}

	/*
	 * WORKAROUND: DWC3 Revisions <1.83a have an issue which, depending
	 * on the link partner, the USB session might do multiple entry/exit
	 * of low power states before a transfer takes place.
	 *
	 * Due to this problem, we might experience lower throughput. The
	 * suggested workaround is to disable DCTL[12:9] bits if we're
	 * transitioning from U1/U2 to U0 and enable those bits again
	 * after a transfer completes and there are no pending transfers
	 * on any of the enabled endpoints.
	 *
	 * This is the first half of that workaround.
	 *
	 * Refers to:
	 *
	 * STAR#9000446952: RTL: Device SS : if U1/U2 ->U0 takes >128us
	 * core send LGO_Ux entering U0
	 */
	if (dwc->revision < DWC3_REVISION_183A) {
		if (next == DWC3_LINK_STATE_U0) {
			u32	u1u2;
			u32	reg;

			switch (dwc->link_state) {
			case DWC3_LINK_STATE_U1:
			case DWC3_LINK_STATE_U2:
				reg = dwc3_readl(dwc->regs, DWC3_DCTL);
				u1u2 = reg & (DWC3_DCTL_INITU2ENA
						| DWC3_DCTL_ACCEPTU2ENA
						| DWC3_DCTL_INITU1ENA
						| DWC3_DCTL_ACCEPTU1ENA);

				if (!dwc->u1u2)
					dwc->u1u2 = reg & u1u2;

				reg &= ~u1u2;

				dwc3_writel(dwc->regs, DWC3_DCTL, reg);
				break;
			default:
				/* do nothing */
				break;
			}
		}
	}

	switch (next) {
	case DWC3_LINK_STATE_U1:
		if (dwc->speed == USB_SPEED_SUPER)
			dwc3_suspend_gadget(dwc);
		break;
	case DWC3_LINK_STATE_U2:
	case DWC3_LINK_STATE_U3:
		dwc3_suspend_gadget(dwc);
		break;
	case DWC3_LINK_STATE_RESUME:
		dwc3_resume_gadget(dwc);
		break;
	default:
		/* do nothing */
		break;
	}

	dwc->link_state = next;
}