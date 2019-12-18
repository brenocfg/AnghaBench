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
struct device_connection {int /*<<< orphan*/ * endpoint; scalar_t__ fwnode; scalar_t__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device* class_find_device_by_fwnode (int /*<<< orphan*/ ,scalar_t__) ; 
 struct device* class_find_device_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_property_present (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  role_class ; 
 void* to_role_switch (struct device*) ; 

__attribute__((used)) static void *usb_role_switch_match(struct device_connection *con, int ep,
				   void *data)
{
	struct device *dev;

	if (con->fwnode) {
		if (con->id && !fwnode_property_present(con->fwnode, con->id))
			return NULL;

		dev = class_find_device_by_fwnode(role_class, con->fwnode);
	} else {
		dev = class_find_device_by_name(role_class, con->endpoint[ep]);
	}

	return dev ? to_role_switch(dev) : ERR_PTR(-EPROBE_DEFER);
}