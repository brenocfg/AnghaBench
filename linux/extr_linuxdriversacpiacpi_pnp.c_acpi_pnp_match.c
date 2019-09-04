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
struct acpi_device_id {scalar_t__* id; } ;

/* Variables and functions */
 struct acpi_device_id* acpi_pnp_device_ids ; 
 scalar_t__ matching_id (char const*,char*) ; 

__attribute__((used)) static bool acpi_pnp_match(const char *idstr, const struct acpi_device_id **matchid)
{
	const struct acpi_device_id *devid;

	for (devid = acpi_pnp_device_ids; devid->id[0]; devid++)
		if (matching_id(idstr, (char *)devid->id)) {
			if (matchid)
				*matchid = devid;

			return true;
		}

	return false;
}