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
typedef  int u64 ;
typedef  int u32 ;
struct acpi_gpe_register_info {int enable_for_run; int mask_for_run; int enable_for_wake; int /*<<< orphan*/  status_address; int /*<<< orphan*/  enable_address; } ;
struct acpi_gpe_event_info {struct acpi_gpe_register_info* register_info; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_event_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVENT_FLAG_ENABLED ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_ENABLE_SET ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_HAS_HANDLER ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_MASKED ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_STATUS_SET ; 
 int /*<<< orphan*/  ACPI_EVENT_FLAG_WAKE_ENABLED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_GPE_DISPATCH_NONE ; 
 scalar_t__ ACPI_GPE_DISPATCH_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_hw_get_gpe_register_bit (struct acpi_gpe_event_info*) ; 
 int /*<<< orphan*/  acpi_hw_read (int*,int /*<<< orphan*/ *) ; 

acpi_status
acpi_hw_get_gpe_status(struct acpi_gpe_event_info *gpe_event_info,
		       acpi_event_status *event_status)
{
	u64 in_byte;
	u32 register_bit;
	struct acpi_gpe_register_info *gpe_register_info;
	acpi_event_status local_event_status = 0;
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	if (!event_status) {
		return (AE_BAD_PARAMETER);
	}

	/* GPE currently handled? */

	if (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) !=
	    ACPI_GPE_DISPATCH_NONE) {
		local_event_status |= ACPI_EVENT_FLAG_HAS_HANDLER;
	}

	/* Get the info block for the entire GPE register */

	gpe_register_info = gpe_event_info->register_info;

	/* Get the register bitmask for this GPE */

	register_bit = acpi_hw_get_gpe_register_bit(gpe_event_info);

	/* GPE currently enabled? (enabled for runtime?) */

	if (register_bit & gpe_register_info->enable_for_run) {
		local_event_status |= ACPI_EVENT_FLAG_ENABLED;
	}

	/* GPE currently masked? (masked for runtime?) */

	if (register_bit & gpe_register_info->mask_for_run) {
		local_event_status |= ACPI_EVENT_FLAG_MASKED;
	}

	/* GPE enabled for wake? */

	if (register_bit & gpe_register_info->enable_for_wake) {
		local_event_status |= ACPI_EVENT_FLAG_WAKE_ENABLED;
	}

	/* GPE currently enabled (enable bit == 1)? */

	status = acpi_hw_read(&in_byte, &gpe_register_info->enable_address);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	if (register_bit & in_byte) {
		local_event_status |= ACPI_EVENT_FLAG_ENABLE_SET;
	}

	/* GPE currently active (status bit == 1)? */

	status = acpi_hw_read(&in_byte, &gpe_register_info->status_address);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	if (register_bit & in_byte) {
		local_event_status |= ACPI_EVENT_FLAG_STATUS_SET;
	}

	/* Set return value */

	(*event_status) = local_event_status;
	return (AE_OK);
}