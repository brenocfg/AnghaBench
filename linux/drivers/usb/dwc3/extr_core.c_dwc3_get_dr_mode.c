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
struct TYPE_2__ {int /*<<< orphan*/  hwparams0; } ;
struct dwc3 {scalar_t__ dr_mode; int /*<<< orphan*/  revision; TYPE_1__ hwparams; struct device* dev; } ;
struct device {int dummy; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_USB_DWC3_GADGET ; 
 int /*<<< orphan*/  CONFIG_USB_DWC3_HOST ; 
 unsigned int DWC3_GHWPARAMS0_MODE (int /*<<< orphan*/ ) ; 
#define  DWC3_GHWPARAMS0_MODE_GADGET 129 
#define  DWC3_GHWPARAMS0_MODE_HOST 128 
 int /*<<< orphan*/  DWC3_REVISION_330A ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int USB_DR_MODE_HOST ; 
 int USB_DR_MODE_OTG ; 
 int USB_DR_MODE_PERIPHERAL ; 
 scalar_t__ USB_DR_MODE_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*) ; 

__attribute__((used)) static int dwc3_get_dr_mode(struct dwc3 *dwc)
{
	enum usb_dr_mode mode;
	struct device *dev = dwc->dev;
	unsigned int hw_mode;

	if (dwc->dr_mode == USB_DR_MODE_UNKNOWN)
		dwc->dr_mode = USB_DR_MODE_OTG;

	mode = dwc->dr_mode;
	hw_mode = DWC3_GHWPARAMS0_MODE(dwc->hwparams.hwparams0);

	switch (hw_mode) {
	case DWC3_GHWPARAMS0_MODE_GADGET:
		if (IS_ENABLED(CONFIG_USB_DWC3_HOST)) {
			dev_err(dev,
				"Controller does not support host mode.\n");
			return -EINVAL;
		}
		mode = USB_DR_MODE_PERIPHERAL;
		break;
	case DWC3_GHWPARAMS0_MODE_HOST:
		if (IS_ENABLED(CONFIG_USB_DWC3_GADGET)) {
			dev_err(dev,
				"Controller does not support device mode.\n");
			return -EINVAL;
		}
		mode = USB_DR_MODE_HOST;
		break;
	default:
		if (IS_ENABLED(CONFIG_USB_DWC3_HOST))
			mode = USB_DR_MODE_HOST;
		else if (IS_ENABLED(CONFIG_USB_DWC3_GADGET))
			mode = USB_DR_MODE_PERIPHERAL;

		/*
		 * DWC_usb31 and DWC_usb3 v3.30a and higher do not support OTG
		 * mode. If the controller supports DRD but the dr_mode is not
		 * specified or set to OTG, then set the mode to peripheral.
		 */
		if (mode == USB_DR_MODE_OTG &&
		    dwc->revision >= DWC3_REVISION_330A)
			mode = USB_DR_MODE_PERIPHERAL;
	}

	if (mode != dwc->dr_mode) {
		dev_warn(dev,
			 "Configuration mismatch. dr_mode forced to %s\n",
			 mode == USB_DR_MODE_HOST ? "host" : "gadget");

		dwc->dr_mode = mode;
	}

	return 0;
}