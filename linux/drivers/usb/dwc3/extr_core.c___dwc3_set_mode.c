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
struct work_struct {int dummy; } ;
struct dwc3 {scalar_t__ dr_mode; int current_dr_role; int desired_dr_role; int /*<<< orphan*/  dev; int /*<<< orphan*/  usb3_generic_phy; int /*<<< orphan*/  usb2_generic_phy; TYPE_1__* usb2_phy; int /*<<< orphan*/  lock; int /*<<< orphan*/  desired_otg_role; scalar_t__ edev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
#define  DWC3_GCTL_PRTCAP_DEVICE 130 
#define  DWC3_GCTL_PRTCAP_HOST 129 
#define  DWC3_GCTL_PRTCAP_OTG 128 
 int /*<<< orphan*/  DWC3_OTG_ROLE_IDLE ; 
 int /*<<< orphan*/  PHY_MODE_USB_DEVICE ; 
 int /*<<< orphan*/  PHY_MODE_USB_HOST ; 
 scalar_t__ USB_DR_MODE_OTG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_event_buffers_cleanup (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_event_buffers_setup (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_exit (struct dwc3*) ; 
 int dwc3_gadget_init (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_host_exit (struct dwc3*) ; 
 int dwc3_host_init (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_exit (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_init (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_otg_update (struct dwc3*,int) ; 
 int /*<<< orphan*/  dwc3_set_prtcap (struct dwc3*,int) ; 
 int /*<<< orphan*/  otg_set_vbus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dwc3* work_to_dwc (struct work_struct*) ; 

__attribute__((used)) static void __dwc3_set_mode(struct work_struct *work)
{
	struct dwc3 *dwc = work_to_dwc(work);
	unsigned long flags;
	int ret;

	if (dwc->dr_mode != USB_DR_MODE_OTG)
		return;

	if (dwc->current_dr_role == DWC3_GCTL_PRTCAP_OTG)
		dwc3_otg_update(dwc, 0);

	if (!dwc->desired_dr_role)
		return;

	if (dwc->desired_dr_role == dwc->current_dr_role)
		return;

	if (dwc->desired_dr_role == DWC3_GCTL_PRTCAP_OTG && dwc->edev)
		return;

	switch (dwc->current_dr_role) {
	case DWC3_GCTL_PRTCAP_HOST:
		dwc3_host_exit(dwc);
		break;
	case DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_gadget_exit(dwc);
		dwc3_event_buffers_cleanup(dwc);
		break;
	case DWC3_GCTL_PRTCAP_OTG:
		dwc3_otg_exit(dwc);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc->desired_otg_role = DWC3_OTG_ROLE_IDLE;
		spin_unlock_irqrestore(&dwc->lock, flags);
		dwc3_otg_update(dwc, 1);
		break;
	default:
		break;
	}

	spin_lock_irqsave(&dwc->lock, flags);

	dwc3_set_prtcap(dwc, dwc->desired_dr_role);

	spin_unlock_irqrestore(&dwc->lock, flags);

	switch (dwc->desired_dr_role) {
	case DWC3_GCTL_PRTCAP_HOST:
		ret = dwc3_host_init(dwc);
		if (ret) {
			dev_err(dwc->dev, "failed to initialize host\n");
		} else {
			if (dwc->usb2_phy)
				otg_set_vbus(dwc->usb2_phy->otg, true);
			phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_HOST);
			phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_HOST);
		}
		break;
	case DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_event_buffers_setup(dwc);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, false);
		phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_DEVICE);
		phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_DEVICE);

		ret = dwc3_gadget_init(dwc);
		if (ret)
			dev_err(dwc->dev, "failed to initialize peripheral\n");
		break;
	case DWC3_GCTL_PRTCAP_OTG:
		dwc3_otg_init(dwc);
		dwc3_otg_update(dwc, 0);
		break;
	default:
		break;
	}

}