#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_hcd {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {scalar_t__ power_down; } ;
struct TYPE_4__ {int port_suspend_change; } ;
struct TYPE_5__ {TYPE_1__ b; } ;
struct dwc2_hsotg {scalar_t__ lx_state; int /*<<< orphan*/  lock; TYPE_3__ params; TYPE_2__ flags; scalar_t__ bus_suspended; scalar_t__ regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  uphy; } ;

/* Variables and functions */
 void* DWC2_L0 ; 
 scalar_t__ DWC2_L2 ; 
 scalar_t__ DWC2_POWER_DOWN_PARAM_PARTIAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  HCD_FLAG_HW_ACCESSIBLE ; 
 int /*<<< orphan*/  HPRT0 ; 
 int HPRT0_CONNDET ; 
 int HPRT0_ENACHG ; 
 int HPRT0_PWR ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ PCGCTL ; 
 int /*<<< orphan*/  PCGCTL_STOPPCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc2_exit_partial_power_down (struct dwc2_hsotg*,int) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 
 scalar_t__ dwc2_is_device_mode (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_port_resume (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_vbus_supply_init (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_phy_set_suspend (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int _dwc2_hcd_resume(struct usb_hcd *hcd)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned long flags;
	u32 pcgctl;
	int ret = 0;

	spin_lock_irqsave(&hsotg->lock, flags);

	if (dwc2_is_device_mode(hsotg))
		goto unlock;

	if (hsotg->lx_state != DWC2_L2)
		goto unlock;

	if (hsotg->params.power_down > DWC2_POWER_DOWN_PARAM_PARTIAL) {
		hsotg->lx_state = DWC2_L0;
		goto unlock;
	}

	/*
	 * Enable power if not already done.
	 * This must not be spinlocked since duration
	 * of this call is unknown.
	 */
	if (!IS_ERR_OR_NULL(hsotg->uphy)) {
		spin_unlock_irqrestore(&hsotg->lock, flags);
		usb_phy_set_suspend(hsotg->uphy, false);
		spin_lock_irqsave(&hsotg->lock, flags);
	}

	if (hsotg->params.power_down == DWC2_POWER_DOWN_PARAM_PARTIAL) {
		/*
		 * Set HW accessible bit before powering on the controller
		 * since an interrupt may rise.
		 */
		set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);


		/* Exit partial_power_down */
		ret = dwc2_exit_partial_power_down(hsotg, true);
		if (ret && (ret != -ENOTSUPP))
			dev_err(hsotg->dev, "exit partial_power_down failed\n");
	} else {
		pcgctl = readl(hsotg->regs + PCGCTL);
		pcgctl &= ~PCGCTL_STOPPCLK;
		writel(pcgctl, hsotg->regs + PCGCTL);
	}

	hsotg->lx_state = DWC2_L0;

	spin_unlock_irqrestore(&hsotg->lock, flags);

	if (hsotg->bus_suspended) {
		spin_lock_irqsave(&hsotg->lock, flags);
		hsotg->flags.b.port_suspend_change = 1;
		spin_unlock_irqrestore(&hsotg->lock, flags);
		dwc2_port_resume(hsotg);
	} else {
		if (hsotg->params.power_down == DWC2_POWER_DOWN_PARAM_PARTIAL) {
			dwc2_vbus_supply_init(hsotg);

			/* Wait for controller to correctly update D+/D- level */
			usleep_range(3000, 5000);
		}

		/*
		 * Clear Port Enable and Port Status changes.
		 * Enable Port Power.
		 */
		dwc2_writel(hsotg, HPRT0_PWR | HPRT0_CONNDET |
				HPRT0_ENACHG, HPRT0);
		/* Wait for controller to detect Port Connect */
		usleep_range(5000, 7000);
	}

	return ret;
unlock:
	spin_unlock_irqrestore(&hsotg->lock, flags);

	return ret;
}