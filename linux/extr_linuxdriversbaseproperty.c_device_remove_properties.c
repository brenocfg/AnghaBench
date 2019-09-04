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
struct property_set {struct device* dev; } ;
struct fwnode_handle {struct fwnode_handle* secondary; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  pset_free_set (struct property_set*) ; 
 int /*<<< orphan*/  set_primary_fwnode (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_secondary_fwnode (struct device*,int /*<<< orphan*/ *) ; 
 struct property_set* to_pset_node (struct fwnode_handle*) ; 

void device_remove_properties(struct device *dev)
{
	struct fwnode_handle *fwnode;
	struct property_set *pset;

	fwnode = dev_fwnode(dev);
	if (!fwnode)
		return;
	/*
	 * Pick either primary or secondary node depending which one holds
	 * the pset. If there is no real firmware node (ACPI/DT) primary
	 * will hold the pset.
	 */
	pset = to_pset_node(fwnode);
	if (pset) {
		set_primary_fwnode(dev, NULL);
	} else {
		pset = to_pset_node(fwnode->secondary);
		if (pset && dev == pset->dev)
			set_secondary_fwnode(dev, NULL);
	}
	if (pset && dev == pset->dev)
		pset_free_set(pset);
}