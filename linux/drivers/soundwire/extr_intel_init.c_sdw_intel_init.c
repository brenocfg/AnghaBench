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
struct sdw_intel_res {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sdw_intel_res*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_intel_acpi_cb ; 
 void* sdw_intel_add_controller (struct sdw_intel_res*) ; 

void *sdw_intel_init(acpi_handle *parent_handle, struct sdw_intel_res *res)
{
	acpi_status status;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE,
				     parent_handle, 1,
				     sdw_intel_acpi_cb,
				     NULL, res, NULL);
	if (ACPI_FAILURE(status))
		return NULL;

	return sdw_intel_add_controller(res);
}