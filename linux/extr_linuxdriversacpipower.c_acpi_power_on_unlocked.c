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
struct acpi_power_resource {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int __acpi_power_on (struct acpi_power_resource*) ; 

__attribute__((used)) static int acpi_power_on_unlocked(struct acpi_power_resource *resource)
{
	int result = 0;

	if (resource->ref_count++) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Power resource [%s] already on\n",
				  resource->name));
	} else {
		result = __acpi_power_on(resource);
		if (result)
			resource->ref_count--;
	}
	return result;
}