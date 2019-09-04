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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_TYPE ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  acpi_deactivate_mem_region ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct resource*,int /*<<< orphan*/ *) ; 

acpi_status acpi_release_memory(acpi_handle handle, struct resource *res,
				u32 level)
{
	if (!(res->flags & IORESOURCE_MEM))
		return AE_TYPE;

	return acpi_walk_namespace(ACPI_TYPE_REGION, handle, level,
				   acpi_deactivate_mem_region, NULL, res, NULL);
}