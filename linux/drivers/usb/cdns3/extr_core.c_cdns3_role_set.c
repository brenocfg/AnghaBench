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
struct cdns3 {int role_override; scalar_t__ dr_mode; int role; int /*<<< orphan*/  dev; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ USB_DR_MODE_HOST ; 
 scalar_t__ USB_DR_MODE_OTG ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
#define  USB_ROLE_DEVICE 130 
#define  USB_ROLE_HOST 129 
#define  USB_ROLE_NONE 128 
 int /*<<< orphan*/  cdns3_hw_role_switch (struct cdns3*) ; 
 int cdns3_role_start (struct cdns3*,int) ; 
 int /*<<< orphan*/  cdns3_role_stop (struct cdns3*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct cdns3* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_role_set(struct device *dev, enum usb_role role)
{
	struct cdns3 *cdns = dev_get_drvdata(dev);
	int ret = 0;

	pm_runtime_get_sync(cdns->dev);

	/*
	 * FIXME: switch role framework should be extended to meet
	 * requirements. Driver assumes that role can be controlled
	 * by SW or HW. Temporary workaround is to use USB_ROLE_NONE to
	 * switch from SW to HW control.
	 *
	 * For dr_mode == USB_DR_MODE_OTG:
	 *	if user sets USB_ROLE_HOST or USB_ROLE_DEVICE then driver
	 *	sets role_override flag and forces that role.
	 *	if user sets USB_ROLE_NONE, driver clears role_override and lets
	 *	HW state machine take over.
	 *
	 * For dr_mode != USB_DR_MODE_OTG:
	 *	Assumptions:
	 *	1. Restricted user control between NONE and dr_mode.
	 *	2. Driver doesn't need to rely on role_override flag.
	 *	3. Driver needs to ensure that HW state machine is never called
	 *	   if dr_mode != USB_DR_MODE_OTG.
	 */
	if (role == USB_ROLE_NONE)
		cdns->role_override = 0;
	else
		cdns->role_override = 1;

	/*
	 * HW state might have changed so driver need to trigger
	 * HW state machine if dr_mode == USB_DR_MODE_OTG.
	 */
	if (!cdns->role_override && cdns->dr_mode == USB_DR_MODE_OTG) {
		cdns3_hw_role_switch(cdns);
		goto pm_put;
	}

	if (cdns->role == role)
		goto pm_put;

	if (cdns->dr_mode == USB_DR_MODE_HOST) {
		switch (role) {
		case USB_ROLE_NONE:
		case USB_ROLE_HOST:
			break;
		default:
			ret = -EPERM;
			goto pm_put;
		}
	}

	if (cdns->dr_mode == USB_DR_MODE_PERIPHERAL) {
		switch (role) {
		case USB_ROLE_NONE:
		case USB_ROLE_DEVICE:
			break;
		default:
			ret = -EPERM;
			goto pm_put;
		}
	}

	cdns3_role_stop(cdns);
	ret = cdns3_role_start(cdns, role);
	if (ret) {
		dev_err(cdns->dev, "set role %d has failed\n", role);
		ret = -EPERM;
	}

pm_put:
	pm_runtime_put_sync(cdns->dev);
	return ret;
}