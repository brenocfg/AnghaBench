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
typedef  int u32 ;
struct acpi_bit_register_info {int access_bit_mask; int bit_position; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_SLEEP_ENABLE ; 
 int /*<<< orphan*/  ACPI_BITREG_SLEEP_TYPE ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGISTER_PM1_CONTROL ; 
 int /*<<< orphan*/  ACPI_STATE_S0 ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int acpi_gbl_sleep_type_a ; 
 int acpi_gbl_sleep_type_b ; 
 int /*<<< orphan*/  acpi_get_sleep_type_data (int /*<<< orphan*/ ,int*,int*) ; 
 struct acpi_bit_register_info* acpi_hw_get_bit_register_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_hw_register_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  acpi_hw_write_pm1_control (int,int) ; 
 int /*<<< orphan*/  hw_legacy_wake_prep ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_hw_legacy_wake_prep(u8 sleep_state)
{
	acpi_status status;
	struct acpi_bit_register_info *sleep_type_reg_info;
	struct acpi_bit_register_info *sleep_enable_reg_info;
	u32 pm1a_control;
	u32 pm1b_control;

	ACPI_FUNCTION_TRACE(hw_legacy_wake_prep);

	/*
	 * Set SLP_TYPE and SLP_EN to state S0.
	 * This is unclear from the ACPI Spec, but it is required
	 * by some machines.
	 */
	status = acpi_get_sleep_type_data(ACPI_STATE_S0,
					  &acpi_gbl_sleep_type_a,
					  &acpi_gbl_sleep_type_b);
	if (ACPI_SUCCESS(status)) {
		sleep_type_reg_info =
		    acpi_hw_get_bit_register_info(ACPI_BITREG_SLEEP_TYPE);
		sleep_enable_reg_info =
		    acpi_hw_get_bit_register_info(ACPI_BITREG_SLEEP_ENABLE);

		/* Get current value of PM1A control */

		status = acpi_hw_register_read(ACPI_REGISTER_PM1_CONTROL,
					       &pm1a_control);
		if (ACPI_SUCCESS(status)) {

			/* Clear the SLP_EN and SLP_TYP fields */

			pm1a_control &= ~(sleep_type_reg_info->access_bit_mask |
					  sleep_enable_reg_info->
					  access_bit_mask);
			pm1b_control = pm1a_control;

			/* Insert the SLP_TYP bits */

			pm1a_control |= (acpi_gbl_sleep_type_a <<
					 sleep_type_reg_info->bit_position);
			pm1b_control |= (acpi_gbl_sleep_type_b <<
					 sleep_type_reg_info->bit_position);

			/* Write the control registers and ignore any errors */

			(void)acpi_hw_write_pm1_control(pm1a_control,
							pm1b_control);
		}
	}

	return_ACPI_STATUS(status);
}