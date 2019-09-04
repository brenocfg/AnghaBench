#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  status_register_id; int /*<<< orphan*/  enable_register_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_WAKE_STATUS ; 
 int /*<<< orphan*/  ACPI_CLEAR_STATUS ; 
 int /*<<< orphan*/  ACPI_ENABLE_EVENT ; 
 size_t ACPI_EVENT_POWER_BUTTON ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SLEEP_TYPE_INVALID ; 
 int /*<<< orphan*/  ACPI_SST_WAKING ; 
 int /*<<< orphan*/  ACPI_SST_WORKING ; 
 int /*<<< orphan*/  METHOD_PATHNAME__SST ; 
 int /*<<< orphan*/  METHOD_PATHNAME__WAK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* acpi_gbl_fixed_event_info ; 
 int /*<<< orphan*/  acpi_gbl_sleep_type_a ; 
 int /*<<< orphan*/  acpi_gbl_system_awake_and_running ; 
 int /*<<< orphan*/  acpi_hw_disable_all_gpes () ; 
 int /*<<< orphan*/  acpi_hw_enable_all_runtime_gpes () ; 
 int /*<<< orphan*/  acpi_hw_execute_sleep_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_legacy_wake ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_hw_legacy_wake(u8 sleep_state)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_legacy_wake);

	/* Ensure enter_sleep_state_prep -> enter_sleep_state ordering */

	acpi_gbl_sleep_type_a = ACPI_SLEEP_TYPE_INVALID;
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, ACPI_SST_WAKING);

	/*
	 * GPEs must be enabled before _WAK is called as GPEs
	 * might get fired there
	 *
	 * Restore the GPEs:
	 * 1) Disable all GPEs
	 * 2) Enable all runtime GPEs
	 */
	status = acpi_hw_disable_all_gpes();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	status = acpi_hw_enable_all_runtime_gpes();
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * Now we can execute _WAK, etc. Some machines require that the GPEs
	 * are enabled before the wake methods are executed.
	 */
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__WAK, sleep_state);

	/*
	 * Some BIOS code assumes that WAK_STS will be cleared on resume
	 * and use it to determine whether the system is rebooting or
	 * resuming. Clear WAK_STS for compatibility.
	 */
	(void)acpi_write_bit_register(ACPI_BITREG_WAKE_STATUS,
				      ACPI_CLEAR_STATUS);
	acpi_gbl_system_awake_and_running = TRUE;

	/* Enable power button */

	(void)
	    acpi_write_bit_register(acpi_gbl_fixed_event_info
				    [ACPI_EVENT_POWER_BUTTON].
				    enable_register_id, ACPI_ENABLE_EVENT);

	(void)
	    acpi_write_bit_register(acpi_gbl_fixed_event_info
				    [ACPI_EVENT_POWER_BUTTON].
				    status_register_id, ACPI_CLEAR_STATUS);

	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, ACPI_SST_WORKING);
	return_ACPI_STATUS(status);
}