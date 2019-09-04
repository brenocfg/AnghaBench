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
struct acpi_gpe_event_info {int /*<<< orphan*/  runtime_count; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_GPE_DISABLE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_update_gpe_enable_mask (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  acpi_hw_low_set_gpe (struct acpi_gpe_event_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_remove_gpe_reference ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_remove_gpe_reference(struct acpi_gpe_event_info *gpe_event_info)
{
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_remove_gpe_reference);

	if (!gpe_event_info->runtime_count) {
		return_ACPI_STATUS(AE_LIMIT);
	}

	gpe_event_info->runtime_count--;
	if (!gpe_event_info->runtime_count) {

		/* Disable on last reference */

		status = acpi_ev_update_gpe_enable_mask(gpe_event_info);
		if (ACPI_SUCCESS(status)) {
			status =
			    acpi_hw_low_set_gpe(gpe_event_info,
						ACPI_GPE_DISABLE);
		}

		if (ACPI_FAILURE(status)) {
			gpe_event_info->runtime_count++;
		}
	}

	return_ACPI_STATUS(status);
}