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
typedef  union acpi_object {int dummy; } acpi_object ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int acpi_data_get_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,union acpi_object const**) ; 
 int /*<<< orphan*/  acpi_device_data_of_node (struct fwnode_handle const*) ; 

int acpi_node_prop_get(const struct fwnode_handle *fwnode,
		       const char *propname, void **valptr)
{
	return acpi_data_get_property(acpi_device_data_of_node(fwnode),
				      propname, ACPI_TYPE_ANY,
				      (const union acpi_object **)valptr);
}