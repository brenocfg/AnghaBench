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
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct usb_bus {scalar_t__ root_hub; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  lx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_L0 ; 
 int /*<<< orphan*/  HCD_FLAG_HW_ACCESSIBLE ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int HPRT0_PWR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_hcd_reinit (struct dwc2_hsotg*) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 
 scalar_t__ dwc2_is_device_mode (struct dwc2_hsotg*) ; 
 int dwc2_read_hprt0 (struct dwc2_hsotg*) ; 
 int dwc2_vbus_supply_init (struct dwc2_hsotg*) ; 
 struct usb_bus* hcd_to_bus (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 

__attribute__((used)) static int _dwc2_hcd_start(struct usb_hcd *hcd)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	struct usb_bus *bus = hcd_to_bus(hcd);
	unsigned long flags;
	u32 hprt0;
	int ret;

	dev_dbg(hsotg->dev, "DWC OTG HCD START\n");

	spin_lock_irqsave(&hsotg->lock, flags);
	hsotg->lx_state = DWC2_L0;
	hcd->state = HC_STATE_RUNNING;
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	if (dwc2_is_device_mode(hsotg)) {
		spin_unlock_irqrestore(&hsotg->lock, flags);
		return 0;	/* why 0 ?? */
	}

	dwc2_hcd_reinit(hsotg);

	hprt0 = dwc2_read_hprt0(hsotg);
	/* Has vbus power been turned on in dwc2_core_host_init ? */
	if (hprt0 & HPRT0_PWR) {
		/* Enable external vbus supply before resuming root hub */
		spin_unlock_irqrestore(&hsotg->lock, flags);
		ret = dwc2_vbus_supply_init(hsotg);
		if (ret)
			return ret;
		spin_lock_irqsave(&hsotg->lock, flags);
	}

	/* Initialize and connect root hub if one is not already attached */
	if (bus->root_hub) {
		dev_dbg(hsotg->dev, "DWC OTG HCD Has Root Hub\n");
		/* Inform the HUB driver to resume */
		usb_hcd_resume_root_hub(hcd);
	}

	spin_unlock_irqrestore(&hsotg->lock, flags);

	return 0;
}