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
struct TYPE_2__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (scalar_t__ (*) (int)) ; 
 int /*<<< orphan*/  ACPI_SST_INDICATOR_OFF ; 
 int /*<<< orphan*/  ACPI_SST_SLEEPING ; 
 int /*<<< orphan*/  ACPI_SST_SLEEP_CONTEXT ; 
 int /*<<< orphan*/  ACPI_SST_WORKING ; 
#define  ACPI_STATE_S0 132 
#define  ACPI_STATE_S1 131 
#define  ACPI_STATE_S2 130 
#define  ACPI_STATE_S3 129 
#define  ACPI_STATE_S4 128 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  METHOD_PATHNAME__PTS ; 
 int /*<<< orphan*/  METHOD_PATHNAME__SST ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_gbl_sleep_type_a ; 
 int /*<<< orphan*/  acpi_gbl_sleep_type_b ; 
 scalar_t__ acpi_get_sleep_type_data (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_hw_execute_sleep_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

acpi_status acpi_enter_sleep_state_prep(u8 sleep_state)
{
	acpi_status status;
	struct acpi_object_list arg_list;
	union acpi_object arg;
	u32 sst_value;

	ACPI_FUNCTION_TRACE(acpi_enter_sleep_state_prep);

	status = acpi_get_sleep_type_data(sleep_state,
					  &acpi_gbl_sleep_type_a,
					  &acpi_gbl_sleep_type_b);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Execute the _PTS method (Prepare To Sleep) */

	arg_list.count = 1;
	arg_list.pointer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.integer.value = sleep_state;

	status =
	    acpi_evaluate_object(NULL, METHOD_PATHNAME__PTS, &arg_list, NULL);
	if (ACPI_FAILURE(status) && status != AE_NOT_FOUND) {
		return_ACPI_STATUS(status);
	}

	/* Setup the argument to the _SST method (System STatus) */

	switch (sleep_state) {
	case ACPI_STATE_S0:

		sst_value = ACPI_SST_WORKING;
		break;

	case ACPI_STATE_S1:
	case ACPI_STATE_S2:
	case ACPI_STATE_S3:

		sst_value = ACPI_SST_SLEEPING;
		break;

	case ACPI_STATE_S4:

		sst_value = ACPI_SST_SLEEP_CONTEXT;
		break;

	default:

		sst_value = ACPI_SST_INDICATOR_OFF;	/* Default is off */
		break;
	}

	/*
	 * Set the system indicators to show the desired sleep state.
	 * _SST is an optional method (return no error if not found)
	 */
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, sst_value);
	return_ACPI_STATUS(AE_OK);
}