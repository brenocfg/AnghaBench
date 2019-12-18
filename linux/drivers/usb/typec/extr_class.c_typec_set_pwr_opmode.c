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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct typec_port {int pwr_opmode; TYPE_1__ dev; } ;
struct typec_partner {int usb_pd; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  enum typec_pwr_opmode { ____Placeholder_typec_pwr_opmode } typec_pwr_opmode ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int TYPEC_PWR_MODE_PD ; 
 struct device* device_find_child (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  partner_match ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct typec_partner* to_typec_partner (struct device*) ; 

void typec_set_pwr_opmode(struct typec_port *port,
			  enum typec_pwr_opmode opmode)
{
	struct device *partner_dev;

	if (port->pwr_opmode == opmode)
		return;

	port->pwr_opmode = opmode;
	sysfs_notify(&port->dev.kobj, NULL, "power_operation_mode");
	kobject_uevent(&port->dev.kobj, KOBJ_CHANGE);

	partner_dev = device_find_child(&port->dev, NULL, partner_match);
	if (partner_dev) {
		struct typec_partner *partner = to_typec_partner(partner_dev);

		if (opmode == TYPEC_PWR_MODE_PD && !partner->usb_pd) {
			partner->usb_pd = 1;
			sysfs_notify(&partner_dev->kobj, NULL,
				     "supports_usb_power_delivery");
		}
		put_device(partner_dev);
	}
}