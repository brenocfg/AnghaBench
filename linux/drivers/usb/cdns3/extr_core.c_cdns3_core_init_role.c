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
struct device {int dummy; } ;
struct cdns3 {int dr_mode; int /*<<< orphan*/  role; struct device* dev; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_USB_CDNS3_GADGET ; 
 int /*<<< orphan*/  CONFIG_USB_CDNS3_HOST ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
#define  USB_DR_MODE_HOST 130 
#define  USB_DR_MODE_OTG 129 
#define  USB_DR_MODE_PERIPHERAL 128 
 int USB_DR_MODE_UNKNOWN ; 
 int /*<<< orphan*/  USB_ROLE_DEVICE ; 
 int /*<<< orphan*/  USB_ROLE_HOST ; 
 int /*<<< orphan*/  USB_ROLE_NONE ; 
 int cdns3_drd_update_mode (struct cdns3*) ; 
 int /*<<< orphan*/  cdns3_exit_roles (struct cdns3*) ; 
 int cdns3_gadget_init (struct cdns3*) ; 
 int cdns3_host_init (struct cdns3*) ; 
 int cdns3_hw_role_switch (struct cdns3*) ; 
 int cdns3_idle_init (struct cdns3*) ; 
 int cdns3_role_start (struct cdns3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int usb_get_dr_mode (struct device*) ; 

__attribute__((used)) static int cdns3_core_init_role(struct cdns3 *cdns)
{
	struct device *dev = cdns->dev;
	enum usb_dr_mode best_dr_mode;
	enum usb_dr_mode dr_mode;
	int ret = 0;

	dr_mode = usb_get_dr_mode(dev);
	cdns->role = USB_ROLE_NONE;

	/*
	 * If driver can't read mode by means of usb_get_dr_mode function then
	 * chooses mode according with Kernel configuration. This setting
	 * can be restricted later depending on strap pin configuration.
	 */
	if (dr_mode == USB_DR_MODE_UNKNOWN) {
		if (IS_ENABLED(CONFIG_USB_CDNS3_HOST) &&
		    IS_ENABLED(CONFIG_USB_CDNS3_GADGET))
			dr_mode = USB_DR_MODE_OTG;
		else if (IS_ENABLED(CONFIG_USB_CDNS3_HOST))
			dr_mode = USB_DR_MODE_HOST;
		else if (IS_ENABLED(CONFIG_USB_CDNS3_GADGET))
			dr_mode = USB_DR_MODE_PERIPHERAL;
	}

	/*
	 * At this point cdns->dr_mode contains strap configuration.
	 * Driver try update this setting considering kernel configuration
	 */
	best_dr_mode = cdns->dr_mode;

	ret = cdns3_idle_init(cdns);
	if (ret)
		return ret;

	if (dr_mode == USB_DR_MODE_OTG) {
		best_dr_mode = cdns->dr_mode;
	} else if (cdns->dr_mode == USB_DR_MODE_OTG) {
		best_dr_mode = dr_mode;
	} else if (cdns->dr_mode != dr_mode) {
		dev_err(dev, "Incorrect DRD configuration\n");
		return -EINVAL;
	}

	dr_mode = best_dr_mode;

	if (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_HOST) {
		ret = cdns3_host_init(cdns);
		if (ret) {
			dev_err(dev, "Host initialization failed with %d\n",
				ret);
			goto err;
		}
	}

	if (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_PERIPHERAL) {
		ret = cdns3_gadget_init(cdns);
		if (ret) {
			dev_err(dev, "Device initialization failed with %d\n",
				ret);
			goto err;
		}
	}

	cdns->dr_mode = dr_mode;

	ret = cdns3_drd_update_mode(cdns);
	if (ret)
		goto err;

	/* Initialize idle role to start with */
	ret = cdns3_role_start(cdns, USB_ROLE_NONE);
	if (ret)
		goto err;

	switch (cdns->dr_mode) {
	case USB_DR_MODE_OTG:
		ret = cdns3_hw_role_switch(cdns);
		if (ret)
			goto err;
		break;
	case USB_DR_MODE_PERIPHERAL:
		ret = cdns3_role_start(cdns, USB_ROLE_DEVICE);
		if (ret)
			goto err;
		break;
	case USB_DR_MODE_HOST:
		ret = cdns3_role_start(cdns, USB_ROLE_HOST);
		if (ret)
			goto err;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	return ret;
err:
	cdns3_exit_roles(cdns);
	return ret;
}