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
 int /*<<< orphan*/  ENODEV ; 
 struct fwnode_handle* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ fwnode_is_primary (struct fwnode_handle*) ; 

void set_secondary_fwnode(struct device *dev, struct fwnode_handle *fwnode)
{
	if (fwnode)
		fwnode->secondary = ERR_PTR(-ENODEV);

	if (fwnode_is_primary(dev->fwnode))
		dev->fwnode->secondary = fwnode;
	else
		dev->fwnode = fwnode;
}