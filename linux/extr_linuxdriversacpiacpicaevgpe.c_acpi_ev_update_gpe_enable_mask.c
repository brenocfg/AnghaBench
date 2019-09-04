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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct acpi_gpe_register_info {int /*<<< orphan*/  enable_for_run; int /*<<< orphan*/  enable_mask; } ;
struct acpi_gpe_event_info {scalar_t__ runtime_count; struct acpi_gpe_register_info* register_info; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CLEAR_BIT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_hw_get_gpe_register_bit (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  ev_update_gpe_enable_mask ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_update_gpe_enable_mask(struct acpi_gpe_event_info *gpe_event_info)
{
	struct acpi_gpe_register_info *gpe_register_info;
	u32 register_bit;

	ACPI_FUNCTION_TRACE(ev_update_gpe_enable_mask);

	gpe_register_info = gpe_event_info->register_info;
	if (!gpe_register_info) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	register_bit = acpi_hw_get_gpe_register_bit(gpe_event_info);

	/* Clear the run bit up front */

	ACPI_CLEAR_BIT(gpe_register_info->enable_for_run, register_bit);

	/* Set the mask bit only if there are references to this GPE */

	if (gpe_event_info->runtime_count) {
		ACPI_SET_BIT(gpe_register_info->enable_for_run,
			     (u8)register_bit);
	}

	gpe_register_info->enable_mask = gpe_register_info->enable_for_run;
	return_ACPI_STATUS(AE_OK);
}