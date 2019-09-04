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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  get_root_bridge_busnr_callback ; 

__attribute__((used)) static acpi_status try_get_root_bridge_busnr(acpi_handle handle,
					     struct resource *res)
{
	acpi_status status;

	res->start = -1;
	status =
	    acpi_walk_resources(handle, METHOD_NAME__CRS,
				get_root_bridge_busnr_callback, res);
	if (ACPI_FAILURE(status))
		return status;
	if (res->start == -1)
		return AE_ERROR;
	return AE_OK;
}