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
struct cdns3 {scalar_t__ dr_mode; int role; int /*<<< orphan*/  dev; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 scalar_t__ USB_DR_MODE_OTG ; 
#define  USB_ROLE_DEVICE 130 
#define  USB_ROLE_HOST 129 
#define  USB_ROLE_NONE 128 
 int cdns3_get_id (struct cdns3*) ; 
 int cdns3_get_vbus (struct cdns3*) ; 
 scalar_t__ cdns3_is_device (struct cdns3*) ; 
 scalar_t__ cdns3_is_host (struct cdns3*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static enum usb_role cdsn3_hw_role_state_machine(struct cdns3 *cdns)
{
	enum usb_role role;
	int id, vbus;

	if (cdns->dr_mode != USB_DR_MODE_OTG)
		goto not_otg;

	id = cdns3_get_id(cdns);
	vbus = cdns3_get_vbus(cdns);

	/*
	 * Role change state machine
	 * Inputs: ID, VBUS
	 * Previous state: cdns->role
	 * Next state: role
	 */
	role = cdns->role;

	switch (role) {
	case USB_ROLE_NONE:
		/*
		 * Driver treats USB_ROLE_NONE synonymous to IDLE state from
		 * controller specification.
		 */
		if (!id)
			role = USB_ROLE_HOST;
		else if (vbus)
			role = USB_ROLE_DEVICE;
		break;
	case USB_ROLE_HOST: /* from HOST, we can only change to NONE */
		if (id)
			role = USB_ROLE_NONE;
		break;
	case USB_ROLE_DEVICE: /* from GADGET, we can only change to NONE*/
		if (!vbus)
			role = USB_ROLE_NONE;
		break;
	}

	dev_dbg(cdns->dev, "role %d -> %d\n", cdns->role, role);

	return role;

not_otg:
	if (cdns3_is_host(cdns))
		role = USB_ROLE_HOST;
	if (cdns3_is_device(cdns))
		role = USB_ROLE_DEVICE;

	return role;
}