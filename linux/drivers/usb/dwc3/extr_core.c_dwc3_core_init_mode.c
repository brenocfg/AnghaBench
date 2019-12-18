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
struct dwc3 {int dr_mode; int /*<<< orphan*/  drd_work; int /*<<< orphan*/  usb3_generic_phy; int /*<<< orphan*/  usb2_generic_phy; TYPE_1__* usb2_phy; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GCTL_PRTCAP_DEVICE ; 
 int /*<<< orphan*/  DWC3_GCTL_PRTCAP_HOST ; 
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_MODE_USB_DEVICE ; 
 int /*<<< orphan*/  PHY_MODE_USB_HOST ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int /*<<< orphan*/  __dwc3_set_mode ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int dwc3_drd_init (struct dwc3*) ; 
 int dwc3_gadget_init (struct dwc3*) ; 
 int dwc3_host_init (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_set_prtcap (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_vbus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_core_init_mode(struct dwc3 *dwc)
{
	struct device *dev = dwc->dev;
	int ret;

	switch (dwc->dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
		dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_DEVICE);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, false);
		phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_DEVICE);
		phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_DEVICE);

		ret = dwc3_gadget_init(dwc);
		if (ret) {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to initialize gadget\n");
			return ret;
		}
		break;
	case USB_DR_MODE_HOST:
		dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_HOST);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, true);
		phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_HOST);
		phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_HOST);

		ret = dwc3_host_init(dwc);
		if (ret) {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to initialize host\n");
			return ret;
		}
		break;
	case USB_DR_MODE_OTG:
		INIT_WORK(&dwc->drd_work, __dwc3_set_mode);
		ret = dwc3_drd_init(dwc);
		if (ret) {
			if (ret != -EPROBE_DEFER)
				dev_err(dev, "failed to initialize dual-role\n");
			return ret;
		}
		break;
	default:
		dev_err(dev, "Unsupported mode of operation %d\n", dwc->dr_mode);
		return -EINVAL;
	}

	return 0;
}