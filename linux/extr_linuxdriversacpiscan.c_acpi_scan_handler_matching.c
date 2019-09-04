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
struct acpi_scan_handler {int (* match ) (char const*,struct acpi_device_id const**) ;struct acpi_device_id* ids; } ;
struct acpi_device_id {scalar_t__* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int stub1 (char const*,struct acpi_device_id const**) ; 

__attribute__((used)) static bool acpi_scan_handler_matching(struct acpi_scan_handler *handler,
				       const char *idstr,
				       const struct acpi_device_id **matchid)
{
	const struct acpi_device_id *devid;

	if (handler->match)
		return handler->match(idstr, matchid);

	for (devid = handler->ids; devid->id[0]; devid++)
		if (!strcmp((char *)devid->id, idstr)) {
			if (matchid)
				*matchid = devid;

			return true;
		}

	return false;
}