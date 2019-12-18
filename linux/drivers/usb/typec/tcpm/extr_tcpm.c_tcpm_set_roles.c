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
struct tcpm_port {scalar_t__ polarity; int pwr_role; int data_role; int /*<<< orphan*/  typec_port; TYPE_1__* tcpc; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;
typedef  enum typec_role { ____Placeholder_typec_role } typec_role ;
typedef  enum typec_orientation { ____Placeholder_typec_orientation } typec_orientation ;
typedef  enum typec_data_role { ____Placeholder_typec_data_role } typec_data_role ;
struct TYPE_2__ {int (* set_roles ) (TYPE_1__*,int,int,int) ;} ;

/* Variables and functions */
 int TYPEC_HOST ; 
 int TYPEC_ORIENTATION_NORMAL ; 
 int TYPEC_ORIENTATION_REVERSE ; 
 scalar_t__ TYPEC_POLARITY_CC1 ; 
 int /*<<< orphan*/  TYPEC_STATE_USB ; 
 int USB_ROLE_DEVICE ; 
 int USB_ROLE_HOST ; 
 int stub1 (TYPE_1__*,int,int,int) ; 
 int tcpm_mux_set (struct tcpm_port*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  typec_set_data_role (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  typec_set_pwr_role (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcpm_set_roles(struct tcpm_port *port, bool attached,
			  enum typec_role role, enum typec_data_role data)
{
	enum typec_orientation orientation;
	enum usb_role usb_role;
	int ret;

	if (port->polarity == TYPEC_POLARITY_CC1)
		orientation = TYPEC_ORIENTATION_NORMAL;
	else
		orientation = TYPEC_ORIENTATION_REVERSE;

	if (data == TYPEC_HOST)
		usb_role = USB_ROLE_HOST;
	else
		usb_role = USB_ROLE_DEVICE;

	ret = tcpm_mux_set(port, TYPEC_STATE_USB, usb_role, orientation);
	if (ret < 0)
		return ret;

	ret = port->tcpc->set_roles(port->tcpc, attached, role, data);
	if (ret < 0)
		return ret;

	port->pwr_role = role;
	port->data_role = data;
	typec_set_data_role(port->typec_port, data);
	typec_set_pwr_role(port->typec_port, role);

	return 0;
}