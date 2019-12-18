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
struct property {int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OF_RECONFIG_UPDATE_PROPERTY ; 
 int __of_update_property (struct device_node*,struct property*,struct property**) ; 
 int /*<<< orphan*/  __of_update_property_sysfs (struct device_node*,struct property*,struct property*) ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_mutex ; 
 int /*<<< orphan*/  of_property_notify (int /*<<< orphan*/ ,struct device_node*,struct property*,struct property*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int of_update_property(struct device_node *np, struct property *newprop)
{
	struct property *oldprop;
	unsigned long flags;
	int rc;

	if (!newprop->name)
		return -EINVAL;

	mutex_lock(&of_mutex);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	rc = __of_update_property(np, newprop, &oldprop);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	if (!rc)
		__of_update_property_sysfs(np, newprop, oldprop);

	mutex_unlock(&of_mutex);

	if (!rc)
		of_property_notify(OF_RECONFIG_UPDATE_PROPERTY, np, newprop, oldprop);

	return rc;
}