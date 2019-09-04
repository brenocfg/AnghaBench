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
struct acpi_resource {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_dev_resource_memory (struct acpi_resource*,struct resource*) ; 

__attribute__((used)) static acpi_status acpi_get_resource_memory(struct acpi_resource *ares,
					    void *context)
{
	struct resource *res = context;

	if (acpi_dev_resource_memory(ares, res))
		return AE_CTRL_TERMINATE;

	return AE_OK;
}