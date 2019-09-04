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
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 struct fwnode_handle* fwnode_get_named_child_node (int /*<<< orphan*/ ,char const*) ; 

struct fwnode_handle *device_get_named_child_node(struct device *dev,
						  const char *childname)
{
	return fwnode_get_named_child_node(dev_fwnode(dev), childname);
}