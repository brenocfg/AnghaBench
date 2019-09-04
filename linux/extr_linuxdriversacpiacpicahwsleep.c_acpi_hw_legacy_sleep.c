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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct acpi_bit_register_info {int access_bit_mask; int bit_position; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_SLEEP_ENABLE ; 
 int /*<<< orphan*/  ACPI_BITREG_SLEEP_TYPE ; 
 int /*<<< orphan*/  ACPI_BITREG_WAKE_STATUS ; 
 int /*<<< orphan*/  ACPI_CLEAR_STATUS ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FLUSH_CPU_CACHE () ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGISTER_PM1_CONTROL ; 
 scalar_t__ ACPI_STATE_S3 ; 
 int ACPI_USEC_PER_SEC ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int acpi_gbl_sleep_type_a ; 
 int acpi_gbl_sleep_type_b ; 
 int /*<<< orphan*/  acpi_gbl_system_awake_and_running ; 
 scalar_t__ acpi_hw_clear_acpi_status () ; 
 scalar_t__ acpi_hw_disable_all_gpes () ; 
 scalar_t__ acpi_hw_enable_all_wakeup_gpes () ; 
 struct acpi_bit_register_info* acpi_hw_get_bit_register_info (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_hw_register_read (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ acpi_hw_register_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ acpi_hw_write_pm1_control (int,int) ; 
 scalar_t__ acpi_os_enter_sleep (scalar_t__,int,int) ; 
 int /*<<< orphan*/  acpi_os_stall (int) ; 
 scalar_t__ acpi_read_bit_register (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ acpi_write_bit_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_legacy_sleep ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status acpi_hw_legacy_sleep(u8 sleep_state)
{
	struct acpi_bit_register_info *sleep_type_reg_info;
	struct acpi_bit_register_info *sleep_enable_reg_info;
	u32 pm1a_control;
	u32 pm1b_control;
	u32 in_value;
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_legacy_sleep);

	sleep_type_reg_info =
	    acpi_hw_get_bit_register_info(ACPI_BITREG_SLEEP_TYPE);
	sleep_enable_reg_info =
	    acpi_hw_get_bit_register_info(ACPI_BITREG_SLEEP_ENABLE);

	/* Clear wake status */

	status = acpi_write_bit_register(ACPI_BITREG_WAKE_STATUS,
					 ACPI_CLEAR_STATUS);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Disable all GPEs */
	status = acpi_hw_disable_all_gpes();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}
	status = acpi_hw_clear_acpi_status();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}
	acpi_gbl_system_awake_and_running = FALSE;

	 /* Enable all wakeup GPEs */
	status = acpi_hw_enable_all_wakeup_gpes();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Get current value of PM1A control */

	status = acpi_hw_register_read(ACPI_REGISTER_PM1_CONTROL,
				       &pm1a_control);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}
	ACPI_DEBUG_PRINT((ACPI_DB_INIT,
			  "Entering sleep state [S%u]\n", sleep_state));

	/* Clear the SLP_EN and SLP_TYP fields */

	pm1a_control &= ~(sleep_type_reg_info->access_bit_mask |
			  sleep_enable_reg_info->access_bit_mask);
	pm1b_control = pm1a_control;

	/* Insert the SLP_TYP bits */

	pm1a_control |=
	    (acpi_gbl_sleep_type_a << sleep_type_reg_info->bit_position);
	pm1b_control |=
	    (acpi_gbl_sleep_type_b << sleep_type_reg_info->bit_position);

	/*
	 * We split the writes of SLP_TYP and SLP_EN to workaround
	 * poorly implemented hardware.
	 */

	/* Write #1: write the SLP_TYP data to the PM1 Control registers */

	status = acpi_hw_write_pm1_control(pm1a_control, pm1b_control);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Insert the sleep enable (SLP_EN) bit */

	pm1a_control |= sleep_enable_reg_info->access_bit_mask;
	pm1b_control |= sleep_enable_reg_info->access_bit_mask;

	/* Flush caches, as per ACPI specification */

	ACPI_FLUSH_CPU_CACHE();

	status = acpi_os_enter_sleep(sleep_state, pm1a_control, pm1b_control);
	if (status == AE_CTRL_TERMINATE) {
		return_ACPI_STATUS(AE_OK);
	}
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Write #2: Write both SLP_TYP + SLP_EN */

	status = acpi_hw_write_pm1_control(pm1a_control, pm1b_control);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	if (sleep_state > ACPI_STATE_S3) {
		/*
		 * We wanted to sleep > S3, but it didn't happen (by virtue of the
		 * fact that we are still executing!)
		 *
		 * Wait ten seconds, then try again. This is to get S4/S5 to work on
		 * all machines.
		 *
		 * We wait so long to allow chipsets that poll this reg very slowly
		 * to still read the right value. Ideally, this block would go
		 * away entirely.
		 */
		acpi_os_stall(10 * ACPI_USEC_PER_SEC);

		status = acpi_hw_register_write(ACPI_REGISTER_PM1_CONTROL,
						sleep_enable_reg_info->
						access_bit_mask);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}

	/* Wait for transition back to Working State */

	do {
		status =
		    acpi_read_bit_register(ACPI_BITREG_WAKE_STATUS, &in_value);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}

	} while (!in_value);

	return_ACPI_STATUS(AE_OK);
}