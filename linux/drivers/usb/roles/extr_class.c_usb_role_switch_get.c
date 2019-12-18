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
struct TYPE_6__ {TYPE_2__* parent; } ;
struct usb_role_switch {TYPE_3__ dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct usb_role_switch*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 struct usb_role_switch* device_connection_find_match (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 struct usb_role_switch* usb_role_switch_is_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_role_switch_match ; 

struct usb_role_switch *usb_role_switch_get(struct device *dev)
{
	struct usb_role_switch *sw;

	sw = usb_role_switch_is_parent(dev_fwnode(dev));
	if (!sw)
		sw = device_connection_find_match(dev, "usb-role-switch", NULL,
						  usb_role_switch_match);

	if (!IS_ERR_OR_NULL(sw))
		WARN_ON(!try_module_get(sw->dev.parent->driver->owner));

	return sw;
}