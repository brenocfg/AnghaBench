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
struct usb_hcd {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {scalar_t__ power_down; } ;
struct dwc2_hsotg {scalar_t__ lx_state; scalar_t__ op_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  uphy; int /*<<< orphan*/  dev; TYPE_1__ params; scalar_t__ regs; int /*<<< orphan*/  bus_suspended; } ;

/* Variables and functions */
 scalar_t__ DWC2_L0 ; 
 scalar_t__ DWC2_L2 ; 
 scalar_t__ DWC2_POWER_DOWN_PARAM_PARTIAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  HCD_FLAG_HW_ACCESSIBLE ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 int /*<<< orphan*/  HPRT0 ; 
 int HPRT0_CONNSTS ; 
 int HPRT0_PWR ; 
 int HPRT0_SUSP ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ OTG_STATE_B_PERIPHERAL ; 
 scalar_t__ PCGCTL ; 
 int PCGCTL_STOPPCLK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc2_enter_partial_power_down (struct dwc2_hsotg*) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 
 scalar_t__ dwc2_is_device_mode (struct dwc2_hsotg*) ; 
 int dwc2_read_hprt0 (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_vbus_supply_exit (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_phy_set_suspend (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int _dwc2_hcd_suspend(struct usb_hcd *hcd)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned long flags;
	int ret = 0;
	u32 hprt0;
	u32 pcgctl;

	spin_lock_irqsave(&hsotg->lock, flags);

	if (dwc2_is_device_mode(hsotg))
		goto unlock;

	if (hsotg->lx_state != DWC2_L0)
		goto unlock;

	if (!HCD_HW_ACCESSIBLE(hcd))
		goto unlock;

	if (hsotg->op_state == OTG_STATE_B_PERIPHERAL)
		goto unlock;

	if (hsotg->params.power_down > DWC2_POWER_DOWN_PARAM_PARTIAL)
		goto skip_power_saving;

	/*
	 * Drive USB suspend and disable port Power
	 * if usb bus is not suspended.
	 */
	if (!hsotg->bus_suspended) {
		hprt0 = dwc2_read_hprt0(hsotg);
		if (hprt0 & HPRT0_CONNSTS) {
			hprt0 |= HPRT0_SUSP;
			if (hsotg->params.power_down == DWC2_POWER_DOWN_PARAM_PARTIAL)
				hprt0 &= ~HPRT0_PWR;
			dwc2_writel(hsotg, hprt0, HPRT0);
		}
		if (hsotg->params.power_down == DWC2_POWER_DOWN_PARAM_PARTIAL) {
			spin_unlock_irqrestore(&hsotg->lock, flags);
			dwc2_vbus_supply_exit(hsotg);
			spin_lock_irqsave(&hsotg->lock, flags);
		} else {
			pcgctl = readl(hsotg->regs + PCGCTL);
			pcgctl |= PCGCTL_STOPPCLK;
			writel(pcgctl, hsotg->regs + PCGCTL);
		}
	}

	if (hsotg->params.power_down == DWC2_POWER_DOWN_PARAM_PARTIAL) {
		/* Enter partial_power_down */
		ret = dwc2_enter_partial_power_down(hsotg);
		if (ret) {
			if (ret != -ENOTSUPP)
				dev_err(hsotg->dev,
					"enter partial_power_down failed\n");
			goto skip_power_saving;
		}

		/* After entering partial_power_down, hardware is no more accessible */
		clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	}

	/* Ask phy to be suspended */
	if (!IS_ERR_OR_NULL(hsotg->uphy)) {
		spin_unlock_irqrestore(&hsotg->lock, flags);
		usb_phy_set_suspend(hsotg->uphy, true);
		spin_lock_irqsave(&hsotg->lock, flags);
	}

skip_power_saving:
	hsotg->lx_state = DWC2_L2;
unlock:
	spin_unlock_irqrestore(&hsotg->lock, flags);

	return ret;
}