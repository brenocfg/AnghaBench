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
struct resource {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int acpi_stm_get_stimulus_area (struct device*,struct resource*) ; 
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 scalar_t__ is_acpi_node (struct fwnode_handle*) ; 
 scalar_t__ is_of_node (struct fwnode_handle*) ; 
 int of_stm_get_stimulus_area (struct device*,struct resource*) ; 

__attribute__((used)) static int stm_get_stimulus_area(struct device *dev, struct resource *res)
{
	struct fwnode_handle *fwnode = dev_fwnode(dev);

	if (is_of_node(fwnode))
		return of_stm_get_stimulus_area(dev, res);
	else if (is_acpi_node(fwnode))
		return acpi_stm_get_stimulus_area(dev, res);
	return -ENOENT;
}