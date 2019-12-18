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
struct acpi_resource {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_RESOURCE_TYPE_GENERIC_REGISTER ; 
 int /*<<< orphan*/  AE_OK ; 

__attribute__((used)) static acpi_status count_registers_cb(struct acpi_resource *ares, void *context)
{
	int *count = context;

	if (ares->type == ACPI_RESOURCE_TYPE_GENERIC_REGISTER)
		++(*count);
	return AE_OK;
}