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
struct resource {int start; } ;
struct fwnode_handle {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE_FWNODE (struct fwnode_handle*) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int acpi_irq_get (int /*<<< orphan*/ ,unsigned int,struct resource*) ; 
 int of_irq_get (struct device_node*,unsigned int) ; 
 struct device_node* to_of_node (struct fwnode_handle*) ; 

int fwnode_irq_get(struct fwnode_handle *fwnode, unsigned int index)
{
	struct device_node *of_node = to_of_node(fwnode);
	struct resource res;
	int ret;

	if (IS_ENABLED(CONFIG_OF) && of_node)
		return of_irq_get(of_node, index);

	ret = acpi_irq_get(ACPI_HANDLE_FWNODE(fwnode), index, &res);
	if (ret)
		return ret;

	return res.start;
}