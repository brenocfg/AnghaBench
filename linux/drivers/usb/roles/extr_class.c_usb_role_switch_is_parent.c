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
struct usb_role_switch {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct usb_role_switch* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device* class_find_device_by_fwnode (int /*<<< orphan*/ ,struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_get_parent (struct fwnode_handle*) ; 
 int /*<<< orphan*/  fwnode_property_present (struct fwnode_handle*,char*) ; 
 int /*<<< orphan*/  role_class ; 
 struct usb_role_switch* to_role_switch (struct device*) ; 

__attribute__((used)) static struct usb_role_switch *
usb_role_switch_is_parent(struct fwnode_handle *fwnode)
{
	struct fwnode_handle *parent = fwnode_get_parent(fwnode);
	struct device *dev;

	if (!parent || !fwnode_property_present(parent, "usb-role-switch"))
		return NULL;

	dev = class_find_device_by_fwnode(role_class, parent);
	return dev ? to_role_switch(dev) : ERR_PTR(-EPROBE_DEFER);
}