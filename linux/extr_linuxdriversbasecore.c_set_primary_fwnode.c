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
struct fwnode_handle {struct fwnode_handle* secondary; } ;
struct device {struct fwnode_handle* fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (struct fwnode_handle*) ; 
 scalar_t__ fwnode_is_primary (struct fwnode_handle*) ; 

void set_primary_fwnode(struct device *dev, struct fwnode_handle *fwnode)
{
	if (fwnode) {
		struct fwnode_handle *fn = dev->fwnode;

		if (fwnode_is_primary(fn))
			fn = fn->secondary;

		if (fn) {
			WARN_ON(fwnode->secondary);
			fwnode->secondary = fn;
		}
		dev->fwnode = fwnode;
	} else {
		dev->fwnode = fwnode_is_primary(dev->fwnode) ?
			dev->fwnode->secondary : NULL;
	}
}