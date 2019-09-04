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
typedef  enum dev_prop_type { ____Placeholder_dev_prop_type } dev_prop_type ;

/* Variables and functions */
 int acpi_data_prop_read (int /*<<< orphan*/ ,char const*,int,void*,size_t) ; 
 int /*<<< orphan*/  acpi_device_data_of_node (struct fwnode_handle const*) ; 

int acpi_node_prop_read(const struct fwnode_handle *fwnode,
			const char *propname, enum dev_prop_type proptype,
			void *val, size_t nval)
{
	return acpi_data_prop_read(acpi_device_data_of_node(fwnode),
				   propname, proptype, val, nval);
}